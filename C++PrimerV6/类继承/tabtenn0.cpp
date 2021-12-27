#include "tabtenn0.h"
#include <iostream>

TableTennisPlayer::TableTennisPlayer(const string &fn, const string &ln, bool ht):firstname(fn),lastname(ln),hastable(ht){}

void TableTennisPlayer::Name() const
{
    cout << lastname << ", " << firstname << '\n';
}


