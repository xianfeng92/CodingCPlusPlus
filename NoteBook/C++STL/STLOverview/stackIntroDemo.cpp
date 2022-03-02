#include <stack>
#include <iostream>

// 栈容器常用接口
void test1()
{
    //创建栈容器 栈容器必须符合先进后出
    stack<int> s;

    s.push(10);
    s.push(20);
    s.push(30);

    while(s.empty())
    {
        // 输出栈顶元素
        cout << "stack top value is " << s.top() << endl;
        // 弹出栈顶元素
        s.pop();
    }

    cout << "stack size is " << s.size() << endl;
}


int main()
{
    test1();
    return 0;
}