#include <iostream>
#include <string>

using namespace std;

int main(int argc, char** argv)
{
    // 没有传入实参, 表示它们均使用 string 的 default 构造函数, 于是都被初始化为空字符串
    string filename, basename, extname, tmpname;
    const string suffix("tmp");

    for(int i =0; i < argc; i++)
    {
        filename = argv[i];
        // 所有查找函数的返回类型都是 string::size_type, 这是 string class 定义的一个无正负号整数类型
        // 字符串 filename 中查找第一个 '.' 字符
        string::size_type idx = filename.find('.');
        // 如果查找失败, 必须返回一个特殊值, 该值就是 npos, 定义于 string class 中
        // 请特别注意, 当你打算检验查找函数的返回值时, 应该使用 string：：size_type 类型而不是 int 或 unsigned。
        // 否则上述与 string：：npos 的比较动作将无法有效运行
        if(idx == string::npos)
        {
            tmpname = filename + '.' + suffix;
        }
        else
        {
            // substr() 的第一实参是起始索引值, 可有可无的第二实参是字符个数(不是终点索引值)
            basename = filename.substr(0, idx);
            // 如果没有指定第二实参, 那么所有剩余字符都将被视为子字符串返回
            extname = filename.substr(idx + 1);
            if(extname.empty())
            {
                tmpname = filename;
                tmpname += suffix;
            }
            else if(extname == suffix)
            {
                tmpname = filename;
                // 是的 size() 和length() 都返回 string 的字符个数
                tmpname = filename.replace(idx + 1, extname.size(), "xxx");
            }
            else
            {
                tmpname = filename;
                // 如果指明 string::npos, 意思是“剩余所有字符"
                tmpname = filename.replace(idx + 1,string::npos, suffix);
            }
        }
    }
    cout << "basename: " << basename << endl;
    cout << "extname: " << extname << endl;
    cout << "filename: " << tmpname << endl;
    cout << "filename: " << filename << endl;
}