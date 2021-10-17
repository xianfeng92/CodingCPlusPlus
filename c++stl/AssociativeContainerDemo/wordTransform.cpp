#include<iostream>
#include<fstream>
#include<sstream>
#include<map>

using namespace std;

map<string, string> buildMap(ifstream &map_file);
const string transform(const string &s, const map<string, string> &m);
void word_transform(ifstream &map_file, ifstream &input);
map<string, string> buildMap(ifstream &map_file)
{
    map<string, string> trans_map;
    string key;
    string value;
    // map_file >> key 读取要转换的单词，存入 key 中； getline(map_file, value) 读取这一行中剩余内容，存入 value 中
    while ((map_file >> key) && getline(map_file, value))
    {
        if (value.size() > 1)
        {
            // substr(1) 跳过分割单词及转换短语之间的前导空格，并将得到的字符串存储 trans_map
            trans_map[key] = value.substr(1);
        }
        else
        {
            throw runtime_error("no rule for " + key);
        }
    }
    // while 循环结束后，trans_map 将保存着用来转换输入文本的规则
    return trans_map;
}

const string transform(const string &s, const map<string, string> &m)
{
    // 实际的转换工作；此部分是程序的核心
    auto map_it = m.find(s);
    if (map_it != m.cend())
    {// 如果单词在转换规则 map 中
        return map_it->second;// 使用替换短语
    }
    else
    {
        return s;// 否则返回原 string
    }
}

void word_transform(ifstream &map_file, ifstream &input)
{
    auto trans_map = buildMap(map_file); // 保存转换规则
    string text;
    while (getline(input, text)) // 读取每一行输入
    {
        istringstream stream(text); // 读取每个单词
        string word;
        while (stream >> word)
        {
            bool firstword = true; // 控制是否打印空格
            if (firstword)
            {
                firstword = false;
            }
            else
            {
                cout << " "; // 在单词间打印一个空格
            }
            cout << transform(word, trans_map); // 打印输出
        }
        cout << endl; // 完成一行的转换
    }
}

int main(int argc, char **argv)
{

    ifstream map_file("transrule.txt");
    ifstream input("rawdate.txt");
    word_transform(map_file, input);
}