#include <iostream>
#include <string>
#include <vector>
#include<set>
#include<map>
#include<iterator>
#include<algorithm>
#include<cctype>
 
using namespace std;
char toLower(char ch) { return tolower(ch); }

string & ToLower(string &st);
void display(const string &str);

int main()
{
    vector<string> words;
    cout << "Enter word(quit to quit):\n ";
    string input;
    while (cin >> input && input != "quit")
    {
        words.push_back(input);
    }
    cout << "You enter the following words:\n ";
    for_each(words.begin(), words.end(),display);
    cout << endl;

    set<string> wordsset;
    transform(words.begin(), words.end(), InsertIterator<set<string>>(wordsset),ToLower);

    cout << "ALphabatic list of words:\n";
    for_each(wordsset.begin(), wordsset.end(),display);
    cout << endl;

    map<string,int> wordmap;
    set<string>::iterator si;
    for(si = wordsset.begin(); si != wordsset.end(); ++si)
    {
        wordmap[*si] = count(wordset.begin(),wordset.end(),*si);
    }

    cout << "DIsplay map contents:\n";
    cout << "word frequencies:\n";
    for(si = wordmap.begin(); si != wordmap.end(); ++si)
    {
        cout << *si << wordmap[*si] << endl;
    }

    string & ToLower(string &str)
    {
        transform(std.begin(), std.end(),toLower);
    }

    void display(const string &str)
    {
        cout << str << endl;
    }

    return 0;
}