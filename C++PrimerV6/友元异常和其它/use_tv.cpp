#include <iostream>
#include "tv.h"

int main()
{
    using std::cout;
    Tv s42;
    cout << "Initial setting for 42 TV is \n";
    s42.settings();
    s42.onoff();
    s42.chanup();
    cout << "Adujust setting for 42 TV is \n";
    s42.chanup();
    s42.settings();

    Remote grey;
    grey.set_chan(s42,10);
    grey.volup();
    grey.volup();

    Tv s58(Tv::On);
    s58.set_mode();
    grey.set_chan(s58,28);
    s58.settings();
    
    return 0;
}