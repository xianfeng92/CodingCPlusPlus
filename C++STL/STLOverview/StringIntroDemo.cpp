#include <string>
#include <iostream>

using std::string;
using std::cout;
using std::endl;

//string构造
void test1()
{
    string s1;// 创建空字符串，调用无参构造函数
    cout <<"s1 is " << s1 << endl;

    const char* str = "helloworld";
    string s2(str);// 把c_string转换成了string
    cout <<"s2 is " << s2 << endl;

    string s3(s2);// 调用拷贝构造函数
    cout <<"s3 is " << s3 << endl;

    string s4(10,'c');
    cout <<"s4 is " << s4 << endl;
}

//赋值
void test1()
{
    string str1;
    str1 = "hello world";
    cout << "str1 is " << str1 << endl;

    string str2;
    str2 = str1;
    cout << "str2 is " << str2 << endl;

    string str3;
    str3 = 'a';
    cout << "str3 is " << str3 << endl;

    string str4;
    str4.assign("hello c++");
    cout << "str4 is " << str4 << endl;

    string str5;
    str5.assign("hello c++",5);
    cout << "str5 is " << str5 << endl;

    string str6;
    str6.assign(str5);
    cout << "str6 is " << str6 << endl;

    string str7;
    str7.assign(5,'x');
    cout << "str7 is " << str7 << endl;
}

//字符串拼接
void test3()
{
    string str1 = "我";

    str1 += "爱玩游戏";

    cout << "str1 = " << str1 << endl;

    str1 += ':';

    cout << "str1 = " << str1 << endl;

    string str2 = "LOL DNF";

    str1 += str2;

    cout << "str1 = " << str1 << endl;

    string str3 = "I";
    str3.append(" love ");
    str3.append("game abcde", 4);
    //str3.append(str2);
    str3.append(str2, 4, 3); // 从下标4位置开始 ，截取3个字符，拼接到字符串末尾
    cout << "str3 = " << str3 << endl;
}


//查找和替换
void test4()
{
    string str1 = "abcdefde";
    int pos = str1.find(de);
    if(pos == -1)
    {
        cout << "未找到";
    }
    else
    {
        cout << "pos = " << pos << endl;
    }
    pos = str1.rfind(de);
    cout << " " << pos << endl;
}

void test5()
{
    string str1 = "abcdefde";
    str1.replace(1,3,"11111");
    cout << "str1 = " << str1 << endl;
}

//字符串比较
void test6()
{

    string s1 = "hello";
    string s2 = "aello";

    int ret = s1.compare(s2);

    if (ret == 0) {
        cout << "s1 等于 s2" << endl;
    }
    else if (ret > 0)
    {
        cout << "s1 大于 s2" << endl;
    }
    else
    {
        cout << "s1 小于 s2" << endl;
    }
}

void test7()
{
    string str = "hello world";
    for(int i = 0; i < str.size(); i++)
    {
        cout << str[i] << endl;
    }
    cout << endl;

    for(int i = 0; i < str.size(); i++)
    {
        cout << str.at(i) << endl;
    }
    cout << endl;
    
    str[0] = 'X';
    str.at(1) = 'Y';
    cout << str << endl;
}

//字符串插入和删除
void test8()
{
    string str = "hello";
    str.insert(1,"111");
    cout << str << endl;

    str.erase(1,3);
    cout << str << endl;
}

void test9()
{
    string str = "abcdefg";
    string substr = str.substr(1, 3);
    cout << substr << endl;

    string email = "hello@example.com";
    int pos = str.find('@');
    string usename = str.substr(0, pos);
    cout << usename << endl;
}

int main()
{
    test1();

    test2();

    test3();

    test4();

    test5();

    test6();

    test7();

    test8();

    test9();

    return 0;
}