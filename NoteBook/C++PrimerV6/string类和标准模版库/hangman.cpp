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
        string target = worldlist[std::rand() % NUM];
        int length = target.length();
        string attempt(length,'-');
        string badchars;
        int guesses = 6;
        cout << "Guess my secret word. It has " << length << " Letters and your guess\n"
        << "one letter at a time. You get " << guesses << " wrong guesses.\n";
        cout << "your word is " << attempt << endl;
        while(guesses > 0 && attempt != target)
        {
            char letter;
            cout << "Guess a letter: ";
            cin >> letter;
            if(badchars.find(letter) != string::npos)
            {
                cout << "You already guess that, Try Again\n";
                continue;
            }
            int loc = target.find(letter);
            if(loc == string::npos)
            {
                cout << "Oh, bad guess!\n";
                --guesses;
                badchars += letter;// add to string
            }
            else
            {
                cout << "Good guess\n";
                attempt[loc] = letter;
                loc = target.find(letter,loc+1);
                while(loc != string::npos)
                {
                    attempt[loc] =letter;
                    loc = target.find(letter,loc+1);
                }
            }
            cout << "your word is " << attempt << endl;

            if(attempt != target)
            {
                if(badchars.length() > 0)
                {
                    cout << "Bad choice " << badchars << endl;
                }
                cout << "guesses " << guesses << endl;
            }
        }
        if(guesses > 0)
        {
            cout << "That right!\n";
        }
        else
        {
            cout << "sorry the word is " << target << ".\n";
            cout << "Will you play again ?"
            cin >> play;
            play = tolower(play);
        }
    }
    cout << "Bye\n";
    return 0;
}