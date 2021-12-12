#include<bitset>// C++ 的 bitset 在 bitset 头文件中，它是一种类似数组的结构，它的每一个元素只能是０或１，每个元素仅用１bit空间
#include<string>
#include<iostream>


using namespace std;


int main(int argc, char **argv)
{

    // !! bitset 构造函数
    // 构造时，需在<>中表明 bitset 的大小(即size)
    bitset<4> bitset1; // 无参构造，长度为４，默认每一位为０

    bitset<8> bitset2(12); // 长度为８，二进制保存，前面用０补充,即为 00001100

    string str("100100100");
    // 用字符串构造时，字符串只能包含 '0' 或 '1' ，否则会抛出异常
    bitset<16> bitset3(str); // bitset3 is 0000000100100100

    // !! 可用的操作符
    bitset<4> foo(string("1001"));
    bitset<4> bar(string("0011"));

    cout << foo ^= bar << endl; // 1010 (foo对bar按位异或后赋值给foo)

    cout << foo &= bar << endl; // 0010 (按位与后赋值给foo)

    cout << (foo |= bar) << endl; // 0011 (按位或后赋值给foo)

    cout << (foo <<= 2) << endl; // 1100 (左移２位，低位补０，有自身赋值)
    cout << (foo >>= 1) << endl; // 0110 (右移１位，高位补０，有自身赋值)

    cout << (~bar) << endl;     // 1100 (按位取反)
    cout << (bar << 1) << endl; // 0110 (左移，不赋值)
    cout << (bar >> 1) << endl; // 0001 (右移，不赋值)

    cout << (foo == bar) << endl; // false (0110==0011为false)
    cout << (foo != bar) << endl; // true  (0110!=0011为true)

    cout << (foo & bar) << endl; // 0010 (按位与，不赋值)
    cout << (foo | bar) << endl; // 0111 (按位或，不赋值)
    cout << (foo ^ bar) << endl; // 0101 (按位异或，不赋值)

    // !! 可以通过[]访问元素(类似数组)，注意最低位下标为０
    // 当然，通过这种方式对某一位元素赋值也是可以的
    bitset<4> tool("1011");

    cout << tool[0] << endl;
    　　 //1
        cout
        << tool[1] << endl;
    　　 //1
        cout
        << tool[2] << endl;
    　　 //0
        cout
        << tool[3] << endl; //1

    // !! 可用函数----bitset还支持一些有意思的函数
    bitset<8> lad("11000110");
    cout << lad.count() << endl;  // count 函数用来求 bitset 中1的位数, output 4
    cout << lad.size() << endl;   //  size函数用来求bitset的大小，output ８
    cout << lad.test(0) << endl;  // test 函数用来查下标处的元素是０还是１，并返回 false 或 true，此处 lad[0]为0，返回 false
    cout << lad.any() << endl;    //  any 函数检查 bitset 中是否有１
    cout << lad.none() << endl;   // none 函数检查 bitset 中是否没有１
    cout << lad.all() << endl;    // all 函数检查bitset中是全部为１
    cout << lad.reset(1) << endl; // reset 函数传一个参数时将参数下标处置为 ０
    cout << lad.reset() << endl;  // reset函数不传参数时将bitset的每一位全部置为０
}