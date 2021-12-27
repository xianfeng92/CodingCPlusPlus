#ifndef B02C88DE_AEA6_41BF_B9DC_A0971545051C
#define B02C88DE_AEA6_41BF_B9DC_A0971545051C

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

#endif /* B02C88DE_AEA6_41BF_B9DC_A0971545051C */
