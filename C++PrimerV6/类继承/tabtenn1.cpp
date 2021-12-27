#include "tabtenn1.h"
#include <iostream>

TableTennisPlayer::TableTennisPlayer(const string &fn, const string &ln, bool ht):firstname(fn),lastname(ln),hastable(ht)
{

}

TableTennisPlayer::Name() const
{
    std::cout << lastname << ", " << firstname << '\n';
}



RatedPlayer::RatedPlayer(unsigned int r, const string &fn, const string & ln, bool ht):TableTennisPlayer(fn, ln, ht),rating(r)
{

}

RatedPlayer::RatedPlayer(unsigned int r, const TableTennisPlayer &rp):TableTennisPlayer(rp),rating(r)
{

}

