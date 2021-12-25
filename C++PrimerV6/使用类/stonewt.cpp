#include <iostream>
#include "stonewt.h"
using std::cout;

Stonewt::Stonewt(double lbs)
{
    stone = int(lbs) / Lbs_per_stn;
    psd_left = int(lbs) % Lbs_per_stn + lbs - int(lbs);
    pounds = lbs;
}


Stonewt::Stonewt(int stn, double lbs)
{
    stone = stn;
    pds_left = lbs;
    pounds = stone * Lbs_per_stn + lbs;
}

Stonewt::Stonewt()
{
    stone = pounds = pds_left = 0;
}


Stonewt::~Stonewt()
{

}

void Stonewt::show_stone() const
{
    cout << stone << "stone, " << pds_left << "pds_left" << '\n';
}

void Stonewt::show_lbs() const
{
    cout << pounds << "pounds \n";
}








