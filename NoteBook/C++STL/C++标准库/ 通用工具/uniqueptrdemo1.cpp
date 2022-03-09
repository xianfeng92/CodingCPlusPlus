#include <iostream>
#include <string>
#include <memory>// for unique_ptr
#include <cstring>// for strerror
#include <cerrno> // for errno

using namespace std;


class DirClose{
public:
    void operator()(DIR *dir){
        if(closedir(dir) != 0)
        {
            std::cerr << "OOPS: closedir() failed" << std::endl;
        }
    }
};


int main(int argc, char *argv[])
{
    unique_ptr<DIR, DirClose> pDir(opendir('.'));

    struct dirent *dp;
    while ((dp = readdir(pDir.get())) != nullptr){
        string filename(dp->d_name);
        cout << "processing " << filename << std::endl;
        ...
    }
}