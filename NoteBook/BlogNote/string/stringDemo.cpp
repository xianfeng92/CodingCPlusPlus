#include <string>
#include <iostream>
#include <stdio.h>
#include <cstring>
#include <algorithm>

using namespace std;

int main(int argc, char** argv)
{
    string strOutput = "Hello, world!";
    //cout 可直接输出 string 类的对象的内容
    cout << "[cout] strOutput is: " << strOutput << endl;

    // string 类型可直接使用 length() 方法计算字符串长度, 该方法计算结果为字符串的实际长度
    int nLen = strOutput.length();

    cout << "[cout] strOutput length is : " << nLen << endl;

    // 使用 c_str() 方法转换 string 类型到 char* 类型时, 需要为 char* 添加 const 关键字
    const char* str = strOutput.c_str();

    cout << "[cout] strOutput data is: " << strOutput.data() << endl;

    // printf() 函数不能直接打印 string 类的对象的内容, 可以通过将 string 转换为 char* 类型，再使用 printf() 函数打印
    printf("[printf] strOutput is %s\n", str);

    string s1("hello");
    string s2(s1);
    string s3(4,'s');// 初始化为 4 个 's'

    const char * a = "test";// 数据存在静态存储区, 不能修改

    char b[] = "test";// 开辟数组再存储, 可以修改
    b[0] = 'P';
    cout << "[cout] array b is " << b <<endl;

    char *c = new char[10];
    memset(c,'\0',sizeof(char)*10);

    cout << "[cout] c is " << c << endl;

    char p[10];

    string str11 = "hello world";
    // 从第 0 个开始复制 5 个, 返回有效复制的数量，需要在 p 最后添加 '\0'
    std::size_t len = str11.copy(p,5,0);
    p[5] = '\0';

    cout << "[cout] len is " << len << endl;

    cout << "[cout] p is " << p << endl;

    char *cstr = new char[str11.length() + 1];
    
    std::strcpy(cstr, str11.c_str());

    cout << "[cout] cstr is " << cstr << endl;

    return 0;
}