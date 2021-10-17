// iostream 处理控制台 io
# include<iostream> // 定义了用于读写流的基本类型 istream(从流读取数据) ostream（向流写入数据） iostream (读写流)

// fstream 处理命名文件 IO
# include<fstream> // 定义了读写命名文件的类型 ifstream--从文件读取数据   ofstream 向文件写入数据 fstream --- 读写文件

// sstream 完成内存 string 的 IO
# include<sstream>  // 定义了读写内存 string 对象的类型 istringstream -- 从 string 读取数据 ostringstream ----向 string 写入数据
# include<vector>

// C++ 使用标准库来处理面向流的输入和输出
using namespace std;



struct PersonInfo{
    string name;
    vector<string> phones;
};

void processFile(ifstream &is){
    ostringstream ostring;
    char buff;
    while(is.get(buff))
    {
        ostring.put(buff);
    }
    // ostring.str() 返回 ostring 所保存的 string 拷贝
    cout << "content is " << ostring.str() << endl;
}

int main(int argc, char ** argv)
{
    // const string filename ="hello.txt";
    // // 当一个 ifstream 离开其作用域时，与之关联的文件会自动关闭
    // // 当一个 ifstream 对象被销毁时，close 会自动被调用
    // ifstream is;
    // is.open(filename);
    // processFile(is);

    // ofstream out;
    // out.open("hello2.txt",ofstream::app);
    // out << "fuck you" << endl;
    // out << "love you" << endl;
    // string line, word;
    // vector<PersonInfo> people;
    // while(getline(cin, line))
    // {
    //     PersonInfo info;
    //     istringstream record(line);
    //     record >> info.name;
    //     if(info.name == "quit"){
    //         cout << "quit, need break" << endl;
    //         break;
    //     }
    //     while(record >> word)
    //     {
    //         info.phones.push_back(word);
    //     }
    //     people.push_back(info);
    // }
    // ofstream ofile("hello2.txt",ofstream::app);
    // for(const auto &people : people){
    //     cout << people.name << endl;
    //     ofile << people.name << endl;
    // }
    // if(ofile.good()){
    //     cout << "gooddddddd" << endl;
    // }

    ofstream ofile("hello.txt", ofstream::app);
    string word;
    while (getline(cin, word))
    {
        if (word == "end")
        {
            cout << "end of input" << endl;
            break;
        }
        if (word == "l")
        {
            cout << endl;
        }
        ofile << word << flush;
    }
}