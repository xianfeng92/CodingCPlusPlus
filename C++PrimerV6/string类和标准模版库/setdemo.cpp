#include<iostream>
#include<set>
#include<algorithm>
#include<iterator>
#include<string>

int main()
{
    using std::cout;
    using std::endl;
    using std::copy;
    using std::ostream_iterator;
    using std::set;
    using std::string;

    const int N = 6;
    string s1[N] = {"buffoon", "thinkers", "for", "heavy", "can", "for"};
    set<string> A(s1,s1+N);
    ostream_iterator<string,char> out(cout, "  ");
    copy(A.begin(),A.end(),out);
    return 0;
}