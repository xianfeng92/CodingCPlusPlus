#ifndef E104167A_A284_4553_8FAB_2659440137C7
#define E104167A_A284_4553_8FAB_2659440137C7

#include<string>

using std::string;

class TableTennisPlayer
{
private:
    string firstname;
    string lastname;
    bool hastable;

public:
    TableTennisPlayer(const string &fn = "none", const string &ln = "none", bool ht = false);
    void Name() const;
    bool HasTable() const { return hastable; }
    void ResetTable(bool v) { hastable = v; }
};


class RatedPlayer: public TableTennisPlayer
{
private:
    unsigned int rating;
public:
    RatedPlayer(unsigned int r = 0, const string &fn = "none", const string &ln ="none", bool ht = false);
    RatedPlayer(unsigned int r = 0, TableTennisPlayer &tp);
    unsigned int rating() const { return rating; }
    void resetRating(unsigned int r) { rating = r; }
};

#endif /* E104167A_A284_4553_8FAB_2659440137C7 */
