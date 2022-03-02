#include<iostream>
#include "mytime1.h"


Time::Time()
{
    hours = minutes = 0;
}

Time::Time(int h, int m)
{
    hours = h;
    minutes = m;
}

void Time::addMinute(int m)
{
    if(minutes + m > 59)
    {
        hours += (minutes + m)/60;
        minutes = (minutes + m)%60;
    }
    else
    {
        minutes += m;
    }
}

void Time::addHour(int h)
{
    hours += h;
}

void Time::reset(int h, int m)
{
    hours = h;
    minutes = m;
}

Time Time::operator+(const Time &t) const
{
    Time sum;
    sum.minutes = minutes + t.minutes;
    sum.hours = hours + t.hours + (minutes + t.minutes)/60;
    sum.minutes = (minutes + t.minutes) % 60;
    return sum;
}

void Time::show() const
{
    std::cout << hours << "hour" << ":" << "minutes" << ":" << minutes << '\n';
}



