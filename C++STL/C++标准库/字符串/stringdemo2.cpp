#include<iostream>
#include<string>

using namespace std;

int main(int argc, char **argv)
{
    // 本程序中, 所有间隔字符被定义于一个特殊的 string 常量内
    const string delims(", \n");
    string line;
    // 外层循环不断地将新行读入 string line 之中
    // getline() 是一个可以从 stream 读取 string 的特殊函数, 它逐字读取, 直到一行结束(通常以换行符作为标志)
    while (getline(cin, line))
    {
        string::size_type begIdx, endIdx;
        // 函数 find_first_not_of() 返回"不隶属于实参所指之 string" 的第一个字符的索引, 所以本例返回第一个"分隔符（delims）以外"
        // 的字符
        begIdx = line.find_first_not_of(delims);
        while (begIdx != string::npos)
        {
            // 内层循环的第一个语句用来查找当前单词的结尾
            endIdx = line.find_first_of(delims, begIdx);
            if(endIdx == string::npos)
            {
                endIdx = line.length();
            }
            // 以下语句将所有字符逆序打印出来
            for(int i = endIdx - 1; i >= static_cast<int>(begIdx); --i)
            {
                cout << line[i];
            }
            cout << ' ';
            // 和先前对 find_first_not_of() 的调用不同, 这里把上一个单词的终点当作查找起点
            begIdx = line.find_first_not_of(delims, endIdx);
        }
    }
}