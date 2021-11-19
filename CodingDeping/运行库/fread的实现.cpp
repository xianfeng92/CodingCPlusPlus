

// !! fread 实现

Windows 下，fread 利用系统 API: ReadFile() 来实现对文件的读取的，但是从 fread 到 ReadFile 之间发生了什么？ IO 是 CRT 最复杂的部分之一。

先来看 fread 函数声明:

size_t fread(void *buffer, size_t elementSize, size_t count, FILE *stream);

size_t: unsigned int 表示数据大小的类型。

'fread 功能是尝试从文件流 stream 读取 count 个大小为 elementSize byte 的数据，存储在 buffer 里，返回实际读取的字节数'。

ReadFile 函数声明:









