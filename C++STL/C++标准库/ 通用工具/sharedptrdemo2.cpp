#include <memory>
#include <fstream>
#include <string>
#include <cstdio>// for remove

using namespace std;


class FileDeleter
{
private:
    string filename;

public:
    FileDeleter(const string& fn):filename(fn)
    {

    }

    void operator()(ofstream& fp)
    {
        fp.close();// close file
        remove(filename.c_str());// delete file
    }
};

int main()
{
    std::shared_ptr<ofstream> fp(new ofstream("hello.txt"), FileDeleter("hello.txt"));
    ...
    return 0;
}