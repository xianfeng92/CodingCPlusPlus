#include <iostream>
#include "tabtenn1.h"

int main()
{
    using std::cout;
    using std::endl;

    TableTennisPlayer player1("Tara","Boomda",true);
    RatedPlayer rplayer1(1140,"Moly","Duck",true);

    rplayer1.Name();

    if(rplayer1.hasTable())
    {
        cout << " Has a table\n";
    }
    else
    {
        cout << " Has no table\n";
    }

    player1.Name();
    if(player1.hasTable())
    {
        cout << " Has a table\n";
    }
    else
    {
        cout << " Has no table\n";
    }
    cout << "Name:";
    rplayer1.Name();
    cout << " Rating : " << rplayer1.rating() << endl;
    RatedPlayer rplayer2(1212,player1);
    cout << "Name:";
    rplayer2.Name();
    cout << " Rating : " << rplayer2.rating() << endl;
    return 0;
}