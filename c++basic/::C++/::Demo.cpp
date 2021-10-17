
using namespace std;

int count=0;    // 全局(::)的count

class A
{
public:
    static int count; // 类 A 的count (A::count)
};

// 静态变量必须在此处定义
int A::count = 1000;

int main(int argc, char **argv)
{
    ::count = 1;  // 设置全局的 count 为1
    A::count = 5; // 设置类A的 count 为 5
    cout << A::count << endl;
    //    int count=3; // 局部 count
    //    count=4;     // 设置局部的 count 为4
    return 0;
}