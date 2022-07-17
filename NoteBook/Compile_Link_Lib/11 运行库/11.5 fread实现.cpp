// !! 11.5　fread 实现

我们知道 C 语言的运行库十分庞大, 前面介绍的启动部分、多线程、全局构造和析构这些内容其实都不是占 CRT 篇幅最大的部分。

'与任何系统级别的软件一样, 真正复杂的并且有挑战性的往往是软件与外部通信的部分, 即 IO 部分'。

首先我们来看 fread 的函数声明:

size_t fread(void* buffer, size_t elementSize, size_t count, FILE *stream)

在这里, size_t 是表示数据大小的类型, 定义为 unsigned int。fread 有 4 个参数, 其功能是尝试从文件流 stream 里读取 count 个大小为 elementSize 个字节的数据,
存储在 buffer 里, 返回实际读取的字节数。


ReadFile 的函数声明为:

bool ReadFile(HANDLE hFile, LPVOID lpbuffer, DWORD nNumberOfBytesToRead, LPWORD lpNumberOfBytesRead, LPOVERLAPPED lpOverlapped);

1. ReadFile 的第一个参数 hFile 为所要读取的文件句柄, 与它对应的应该是 fread 里面的 stream 参数;

2. 第二个参数 lpBuffer 是读取文件内容的缓冲区, 相对应的 fread 参数为 buffer

3. 第三个参数 nNumberOfBytesToRead 为要读取多少字节, fread 与它相对应的应该是两个参数的乘积, 即 elementSize * count

4. 第四个参数 lpNumberOfBytesRead 为一个指向 DWORD 类型的指针, 它用于返回读取了多少个字节

5. 最后一个参数是没用的，可以忽略它


在了解了 fread 函数和 ReadFile 函数之后, 可以发现它们在功能上看似完全相同, 而且在参数上几乎一一对应, 所以如果我们要实现一个最简单的 fread 就是直接调用 ReadFile
而不做任何处理:

size_t fread(void* buffer, size_t elementSize, size_t count, FILE *stream) {
    DWORD bytesRead = 0;
    bool ret = ReadFile(stream->_file, buffer, count * elementSize, &bytesRead, NULL);
    if(ret) {
        return bytesRead;
    }
    return -1;
}


// !! 11.5.1　缓冲

对于 glibc, fread 的实现过于复杂, 因此我们这里选择 MSVC 的 fread 实现。但在阅读 fread 的代码之前, 首先要介绍一下缓冲 Buffer 的概念。

缓冲最为常见于 IO 系统中, 设想一下, 当希望向屏幕输出数据的时候, 由于程序逻辑的关系, 可能要多次调用 printf 函数, 并且每次写入的数据只有几个字符, 如果每次写数据都要进
行一次系统调用, 让内核向屏幕写数据, 就明显过于低效了, 因为系统调用的开销是很大的, 它要进行上下文切换、内核参数检查、复制等, '如果频繁进行系统调用, 将会严重影响程序和系
的性能'。

'一个显而易见的可行方案是将对控制台连续的多次写入放在一个数组里, 等到数组被填满之后再一次性完成系统调用写入, 实际上这就是缓冲最基本的想法'。

当读文件的时候, 缓冲同样存在。我们可以在 CRT 中为文件建立一个缓冲, 当要读取数据的时候, 首先看看这个文件的缓冲里有没有数据, 如果有数据就直接从缓冲中取。
如果缓冲是空的, 那么 CRT 就通过操作系统一次性读取文件一块较大的内容填充缓冲。这样, 如果每次读取文件都是一些尺寸很小的数据, 那么这些读取操作大多都直接从缓冲中获得, 可以
避免大量的实际文件访问。

除了读文件有缓冲以外, 写文件也存在着同样的情况, 而且写文件比读文件要更加复杂, 因为当我们通过 fwrite 向文件写入一段数据时, 此时这些数据不一定被真正地写入到文件中, 而是有
可能还存在于文件的写缓冲里面, 那么此时如果系统崩溃或进程意外退出时, 有可能导致数据丢失, 于是 CRT 还提供了一系列与缓冲相关的操作用于弥补缓冲所带来的问题。

C 语言标准库提供与缓冲相关的几个基本函数, 如表 11-4 所示。

'所谓 flush 一个缓冲, 是指对写缓冲而言, 将缓冲内的数据全部写入实际的文件, 并将缓冲清空, 这样可以保证文件处于最新的状态'。

'之所以需要 flush, 是因为写缓冲使得文件处于一种不同步的状态, 逻辑上一些数据已经写入了文件, 但实际上这些数据仍然在缓冲中', 如果此时程序意外地退出 (发生异常或断电等), 那
么缓冲里的数据将没有机会写入文件。flush 可以在一定程度上避免这样的情况发生。

在这个表中我们还能看到 C 语言支持两种缓冲, 即行缓冲 (Line Buffer) 和全缓冲 (Full Buffer)。

全缓冲是经典的缓冲形式, 除了用户手动调用 fflush 外, 仅当缓冲满的时候, 缓冲才会被自动 flush 掉。

而行缓冲则比较特殊, 这种缓冲仅用于文本文件, 在输入输出遇到一个换行符时, 缓冲就会被自动 flush, 因此叫行缓冲。


// !! 11.5.2　fread_s

在了解了缓冲的大致内容之后, 让我们回到 fread 的代码分析。MSVC 的 fread 的定义在 crt/fread.c 里, 实际内容只有一行:

size_t _fread_nolock( void* buffer, size_t elementSize, size_t count, FILE* stream) {
    return fread_s(buffer, SIZE_MAX, elementSize ,count, stream);
}

可见 fread 将所有的工作都转交给了 _fread_ s。fread_s 定义如下:

fread -> fread_s:

size_t cdecl fread_s(void* buffer, size_t bufferSize, size_t elementSize, size_t count, FILE *stream) {
    ...
    _lock_str(stream);
    retval = _fread_nolock_s(buffer, bufferSize, elementSize, count, stream);
    _unlock_str(stream);
    return retval;
}

fread_s 的参数比 fread 多一个 bufferSize, 这个参数用于指定参数 buffer 的大小。在 fread 中, 这个参数直接被定义为 SIZE_MAX 即 size_t 的最大值, 表明 fread 不
关心这个参数。而用户在使用 fread_s 时就可以指定这个参数, 以达到防止越界的目的 (fread_s 的 s 是 safe 的意思)。

fread_s 首先对各个参数检查, 然后使用 _lock_str 对文件进行加锁, 以防止多个线程同时读取文件而导致缓冲区不一致。

我们可以看到 fread_s 其实又把工作交给了 _fread_nolock_s。


// !! 11.5.3　fread_nolock_s

fread_nolock_s 是进行实际工作的函数, 为了便于理解, 下面会分段列出 fread_nolock_s 的实现, 并且将省去所有的参数检查和错误检查。

fread -> fread_s -> _fread_nolock_s:

size_t __cdecl _fread_nolock_s(void* buffer, size_t bufferSize, size_t elementSize, size_t num, FILE *stream){
    char *data;
    size_t dataSize;
    size_t total;
    size_t count;
    unsigned streamBufferSize;
    unsigned nbytes;
    unsigned nread;
    int c;

    data = buffer;
    dataSize = bufferSize;
    count = total = elementSize * num;
    ...
}

这一段是 fread_nolock_s 的初始化部分。在它的局部变量中, data 将始终指向 buffer 中尚未被写入的起始部分。在最开始的时候, data 指向 buffer 的开头。dataSize 记录
了 buffer 中还可以写入的字节数, 理论上, data + dataSize = buffer + bufferSize。如图 11-12 所示。

total 变量记录了总共须要读取的字节数, count 则记录在读取过程中尚未读的字节数。streambufsize 记录了文件缓冲的大小。

在对缓冲的概念有了一定了解之后, 可分析一下文件类型 FILE 结构的定义了。FILE 的定义位于 stdio.h 里:

struct _iobuf {
    char* _ptr;
    int _cnt;
    char* _base;
    int _flag;
    int _file;
    int _charbuf;
    int _bufsiz;
    char* _tmpfname;
};

typedef struct _iobuf FILE;

在这里, _base 字段指向一个字符数组, 即这个文件的缓冲, 而 _bufsiz 记录着这个缓冲的大小。

_ptr 和 fread_nolock_s 的局部变量 data 一样, 指向 buffer 中第一个未读的字节, 而 _cnt 记录剩余未读字节的个数。

_flag 记录了 FILE 结构所代表的打开文件的一些属性, 目前我们感兴趣的是 3 个标志:

#define _IOYOURBUF 0x0100 
#define _IOMYBUF 0x0008
#define _IONBF 0x0004


在这里, _IOYOURBUF 代表这个文件使用用户通过 setbuf 提供的 buffer, _IOMYBUF 代表这个文件使用内部的缓冲, 而 _IONBF 代表这个文件使用一个单字节的缓冲, 即缓冲大小仅
为 1 个字节。

这个缓冲就是 _charbuf 变量。此时, _base 变量的值是无效的。接下来继续看 fread_nolock_s 的代码:

if (anybuf(stream)){
    streambufsize = stream->_bufsiz;
}else {
    streambufsize = _INTERNAL_BUFSIZ;
}

anybuf 函数的定义位于 file2.h: 

#define anybuf(s) \   ((s)->_flag & (_IOMYBUF|_IONBF|_IOYOURBUF))

事实上 anybuf 并不是函数, 而是一个宏, 它仅检查这个 FILE 结构的 _flag 变量里有没有前面提到的 3 个标志位的任意一个, 如果这 3 个标志位在 _flag 中存在任意一个, 就说明
这个文件使用了缓冲。

这一段代码对 streambufsize 变量进行了赋值, 如果文件自己有 buffer, 那么 streambufsize 就等于这个 buffer 的大小; 如果文件没有使用 buffer, 那么 fread_nolock_s
就会使用一个内部的 buffer, 这个 buffer 的大小固定为 _INTERNAL_BUFSIZ, 即 4096 字节。


while (count != 0) {
    read data
    decrease count
}

循环体内的操作用伪代码表示, 大致的意思是: 每一次循环都从文件中读取一部分数据, 并且相应地减少 count (count 代表还没有读取的字节数)。

当读取数据时, 根据文件是否使用 buffer 及读取数据的多少分为 3 种情况, 下面我们一一来看:

if (anybuf(stream) && stream->_cnt != 0) {
    nbytes = (count < stream->_cnt) ? count : stream->_cnt;
    memcpy_s(data, dataSize, stream->_ptr, nbytes);
    count -= nbytes;
    stream->_cnt -= nbytes;
    stream->_ptr += nbytes;
    data += nbytes;
    dataSize -= nbytes;
}

在 if 的判断句中, anybuf 判断文件是否有缓冲, 而 stream->_cnt != 0 判断缓冲是否为空。因此当且仅当文件有缓冲且不为空时, 这段代码才会执行。

让我们一行一行地来看这段代码的作用。nbytes 代表这次要从缓冲中读取多少字节。在这里, nbytes 等于还须要读取的字节数 (count) 与缓冲剩余的字节数 (stream->_cnt) 中较小
的一个。

接下来的一行使用 memcpy_s 将文件 stream 里 _ptr 所指向的缓冲内容复制到 data 指向的位置, 如图 11-13 所示。

接下来的 5 行, 皆是按照图 11-13 修正 FILE 结构和局部变量的各种数据。


memcpy_s 是 memcpy 的安全版本, 相对于原始的 memcpy 版本, memcpy_s 接受一个额外的参数记录输出缓冲区的大小, 以防止越界, 其余的功能和 memcpy 相同。

以上代码处理了文件缓冲不为空的情况, 而如果缓冲为空, 那么又分为两种情况:

1. 需要读取的数据大于缓冲的尺寸

2. 需要读取的数据不大于缓冲的尺寸

对于情况 1, fread 将试图一次性读取尽可能多的整数个缓冲的数据直接进入输出的数组中, 如果缓冲尺寸为 0, 则直接将剩下的数据一次性读取。
代码如下:

else if (count >= bufsize) {
    nbytes = ( bufsize ? (unsigned)(count - count % bufsize) : (unsigned)count);
    nread = _read(_fileno(stream), data, nbytes);
    if (nread == 0) {
        stream->_flag |= _IOEOF;
        return (total - count) / size;
    }else if (nread == (unsigned)-1) {
        stream->_flag |= _IOERR;
        return (total - count) / size;
    }
    count -= nread;
    data += nread;
}


如果要读取的数据不大于缓冲的尺寸, 那么仅需要重新填充缓冲即可:

else {
    if ((c = _filbuf(stream)) == EOF) {
        return (total - count) / size;
    }
    *data++ = (char) c;
    --count;
    bufsize = stream->_bufsiz;
}

_filbuf 函数负责填充缓冲。该函数的具体实现重要的部分只有一行:

stream->_cnt = _read(_fileno(stream), stream->_base, stream->_bufsiz);

可以看见所有的线索都指向了 _read 函数。_read 函数主要负责两件事:

1. 从文件中读取数据

2. 对文本模式打开的文件, 转换回车符


// !! 11.5.4　_read

_read 的代码位于 crt/src/read.c。在省略了一部分无关紧要的代码之后, 其内容如下:

fread -> fread_s -> _fread_nolock_s -> _read:

int __cdecl _read(int fh, void* buf, unsigned cnt) {
    int bytes_read;                 /* number of bytes read */
    char *buffer;                   /* buffer to read to */
    int os_read;                    /* bytes read on OS call */
    char *p, *q;                    /* pointers into buffer */
    char peekchr;                   /* peek-ahead character */
    ULONG dosretval;                /* o.s. return value */
    bytes_read = 0;                 /* nothing read yet */
    buffer = buf;
     ...
}


这部分是 _read 函数的参数、局部变量和初始化部分。下面的代码处理一个单字节缓冲:

if ((_osfile(fh) & (FPIPE|FDEV)) && _pipech(fh) != LF) {
     *buffer++ = _pipech(fh);
      ++bytes_read;
      --cnt;
       _pipech(fh) = LF;
}

_read 函数在每次读取管道和设备数据的时候必须先检查 pipech, 以免漏掉一个字节。在处理完这个单字节缓冲之后,接下来的内容是实际的文件读取部分:


if ( !ReadFile( (HANDLE)_osfhnd(fh), buffer, cnt, (LPDWORD)&os_read, NULL)){
    ...
}

在这里我们可以看到 ReadFile 接管了 _read 的第一个职责。


// !! 11.5.5　文本换行

接下来 _read 要为以文本模式打开的文件转换回车符。

Linux/Unix: 回车用 \n 表示

Mac OS: 回车用\r表示

Windows: 回车用\r\n表示


而在 C 语言中, 回车始终用 \n 来表示, 因此在以文本模式读取文件的时候, 不同的操作系统需要将各自的回车符表示转换为 C 语言的形式。也就是:

Linux/Unix: 不做改变

Mac OS: 每遇到 \r 就将其改为 \n

Windows: 将 \r\n 改为 \n



// !! 11.5.6　fread 回顾

当用户调用 CRT 的 fread 时, 它到 ReadFile 的调用轨迹如图 11-15 所示。

在这个轨迹中, _fread_nolock_s 的实现是最复杂的, 因为它涉及缓冲区的操作, 它也是读取文件的主要部分, 如果我们使用 fread 读取一小块数据, 有可能在 _fread_nolock_s 
的时候发现所有所需要的数据都在缓冲中, 就不需要通过 _read 和 ReadFile 向操作系统读取文件了, 而是直接从缓冲区复制数据并返回, 这样就减少了系统调用的开销。



