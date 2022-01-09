#include<iostream>
#include "tv.h"

bool Tv::volup()
{
    if(volume < MaxVal)
    {
        volume++;
        return true;
    }
    return false;
}

bool Tv::voldown()
{
    if(volume > MaxVal)
    {
        volume--;
        return true;
    }
    return false;
}

void Tv::chanup()
{
    if(channel < maxchannel)
    {
        channel++;
    }
    else
    {
        channel = 1;
    }
}

void Tv::chandown()
{
    if(channel > 1)
    {
        channel--;
    }
    else
    {
        channel = maxchannel;
    }
}

void Tv::settings() const
{
    using std::cout;
    using std::endl;

    cout << "Tv is " << state == Off ? "OFF" : "ON" << endl;
    cout << "Channel setting is " << channel << endl;
    cout << "Mode is " << (Mode == Antenna) ? "Antenna":"Cable" << endl;
    cout << "Input is " << (Input == TV)?"TV":"DVD" << endl;
    
}


