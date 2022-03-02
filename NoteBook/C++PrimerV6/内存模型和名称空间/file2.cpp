//file2.cpp

#include<iostream>
#include<cmath>
#include"coordin.h"

polar rect_to_polar(rect xypos)
{
    using namespace std;
    polar answer;
    answer.distance = sqrt(xypos.x*xypos.x + xypos.y*xypos.y);
    answer.angle = atan2(xypos.x,xypos.y);
    return answer;
}


void show_polar(polar dapos)
{
    using namespace std;
    const double Red_to_deg = 57.29577;
    cout << "distance: " << dapos.distance;
    cout << " angle: " << dapos.angle * Red_to_deg;
    out << "degrees\n"
}
