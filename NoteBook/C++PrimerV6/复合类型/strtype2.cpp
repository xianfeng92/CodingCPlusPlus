// strtype2.cpp

#include<iostream>
#include<string>

int main()
{
    using namespace std;
    string s1 = "penguin";
    string s2,s3;

    cout << "You can assign one string Object to another : s2 = s1\n";
    cout << "s2 = \"buzzard\"\n";
    s2 = "buzzard";
    cout <<"s2: " << s2 << endl;
    cout << "you can concatenate string : s3 = s2 + s1 \n";
    s3 = s2 + s1;
    cout << "s3: " << s3 << endl;
    cout << " you can append string .\n";
    s1 += s2;
    cout << "s1 += s2 yields s1 =  " << s1 << endl;
    s2 += "for a day";
    cout << "s2 += \"for a day\" yields s2 = " << s2 << endl;

    return 0;
}