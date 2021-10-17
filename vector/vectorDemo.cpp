# include<iostream>
# include<vector>

using namespace std;

int main()
{
    // // 默认初始化，lists 中不包含任何元素
    // vector<string> lists;
    // lists.push_back("hello");
    // lists.push_back("world");
    // lists.push_back("haha");
    // lists.push_back("yes");

    // char buffer[222] = "hello world"

    // for(vector<string>::const_iterator it = lists.begin(); it != lists.end(); ++it)
    // {
    //     cout << it->first << " " << endl;
    // }
    // cout << "list 1 index value is " << lists[1] << endl;

    // string list("helloworld");
    // for(list.begin() != lists.end())
    // {
    //     auto it = list.begin();
    //     *it = toupper(*it);
    // }
    
    // int ia [] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14};

    // int * beg = begin(ia);
    // int * last = end(ia);
    // while(beg != last && *beg > 0)
    // {
    //     ++ beg;
    // }
    // if(beg != last)
    // {
    //   cout << *beg << endl;
    // }
    // else
    // {
    //  cout << "oppppps" << endl;
    // }


    string lists [] = {"tell","me","a","joke"};
    string * beg = begin(lists);
    cout << *(beg + 3) << endl;
}