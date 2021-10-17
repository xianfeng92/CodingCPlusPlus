#include<iostream>

// 标准库定义的所有名字都在命名空间 std 中
using namespace std;

int main(){
    // write byte to stream
    cout << "Enter two number"<<endl;// << 输出运算符 "Enter two number" 为字符串字面值常量
    int v1,v2;
    cin >> v1>>v2;// >> 输入运算符
    cout << "V1 value is "<<v1<<endl;
    cout << "V2 value is "<<v2<<endl;
    cout << "The sum of the two numbers is "<<v1+v2<<endl;
    int count = 0;
    while(count <= 100){
        cout << count << endl;
        ++ count;
    }
    // ++i 前缀递增运算符
    for(int i=0; i<count; ++i){
        cout << i << endl;
    }
    return 100;
}