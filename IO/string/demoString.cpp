# include<string>
# include<iostream>
# include<algorithm>

using namespace std;

int main()
{
    // string s1,s2;
    // cin >> s1 >> s2;
    // cout << "s1 is " << s1 << endl;
    // cout << "s2 is " << s2 << endl;

    // string s1;
    // while(cin >> s1){
    //     cout << s1 << endl;
    // }

    // string s1;
    // getline(cin, s1);
    // cout << s1 << endl;
    // cout << "s1 size is " << s1.size() << endl;

    // string s1;

    // while(getline(cin,s1)){
    //     if(!s1.empty()){
    //         cout << s1 << endl;
    //     }
    // }

    struct database {
        int count = 10;
        int  s = 22;
        int count2 = 10;
    };

    database data;

    string s = "tellmeajoke";

    int  i = 1222;

    string s1("hello");
    string s2("world");
    string s3 = s1 + s2;
    // transform(s3.begin(), s3.end(), s3.begin(),::toupper);
    //     cout << s3 << endl;
    for(auto &ss : s3){
        ss = toupper(ss);
    }
    if(!s3.empty()){
        cout << s3[0] << endl;
    }
    cout << s3 << endl;

    cout << "s size is " << s.size() << endl;
    cout << "size of s is  " << sizeof(data) << endl;
    return 0;
}