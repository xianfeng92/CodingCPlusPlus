# include <cstring>
# include <iostream>

using namespace std;

// 对于大多数应用来说，使用标准库 string 要比使用 C 风格字符串更安全、更高效
int main()
{
    // C 风格字符串不是一种类型，而是为了表达和使用字符串而形成的一种约定俗成的写法。
    // 按此习惯写书的字符串存在字符数组中并以空字符结束（‘\0’） 
    char buf[] = "hello world";
    char str[] = "hello world";

    string boys = "tfboys";

    const char * cboys = boys.c_str();

    cout << strlen(cboys) << endl;

    char buffer [] = {'1','2','\0'};

    char buf2[100];

    cout <<strlen(buf) << endl;
    cout <<strcmp(buf,str) << endl;

    strcpy(buf2,buf);

    cout << buf2 << endl;

    cout << strlen(buffer) << endl;

}
