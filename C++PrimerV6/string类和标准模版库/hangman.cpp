#include<iostream>
#include<string>
#include<cstdlib>
#include<ctime>
#include<cctype>

using std::string;
const int NUM = 26;
const string worldlist[NUM] = 
{
    "applist","bee","hello","worldlist","Sorry","please","enter","your","name","help",
    "me","get","it","done","see","about","NOT","tiom","shares","Student","shortest",
    "other","full","funny","integer","xforg"
}

int main()
{
    using std::cout;
    using std::endl;
    using std::cin;
    using std::tolower;

    std::srand(std::time(NULL));
    char play;
    cout << "Will you play a word game ?<y/n>\n";
    cin >> play;
    play = tolower(play);
    while(play == 'y')
    {
        
    }
}