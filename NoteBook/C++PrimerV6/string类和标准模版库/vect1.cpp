#include<iostream>
#include<string>
#include<vector>

const int NUM =5;

int main()
{
    using std::vector;
    using std::string;
    using std::endl;
    using std::cin;
    using std::cout;

    vector<int> ratings(NUM);
    vector<string> titles(NUM);
    cout << "You will do exactly as told. you will enter\n" << NUM << " book titles and you rating (0-10):\n";
    int i;
    for(i=0; i<NUM; i++)
    {
        cout << "Enter title # " << i+1 << " : ";
        getline(cin,title[i]);
        cin >> ratings[i];
        cin.get();
    }
    cout << "Thank you. You Entered the following book:\n"
    << "Ratings\tbook\t";
    for(int i = 0; i < NUM; i++)
    {
        cout << ratings[i] << "\t" << title[i] << "\n";
    }
    return 0;
}