// travel.cpp

#include<iostream>

struct travel_time {
    int hour;
    int minute;
};

const int Minis_per_hour = 60;

travel_time sum(travel_time t1, travel_time t2);

void show_time(travel_time t);

int main()
{
    using namespace std;
    travel_time day1 = {2,3};
    travel_time day2 = {4,5};
    travel_time trip = sum(day1, day2);
    cout << "two days total:\n";
    show_time(trip);
    travel_time day3 = {5,2};
    cout << "three days total:\n";
    travel_time sum3 = sum(day3,trip);
    show_time(sum3);
    return 0;
}

travel_time sum(travel_time t1, travel_time t2)
{
    travel_time total;
    total.minute = (t1.minute + t2.minute) % Minis_per_hour;
    total.hour = (t1.hour + t2.hour) + (t1.minute + t2.minute)/Minis_per_hour;
    return total;
}

void show_time(travel_time t)
{
    using namespace std;
    cout << t.hour << " hours, " << t.minute << " minite " << endl;
}


