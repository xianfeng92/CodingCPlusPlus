#include <iostream>
#include <chrono>

using namespace std;

// struct Point3d{
//     float x, y, z;
// };


class Point3d{
    public:
        float x_, y_, z_;
        Point3d() : x_(0), y_(0), z_(0){}
        Point3d(float x, float y, float z):x_(x), y_(y), z_(z){}
};

Point3d Lots_of_copy(Point3d a, Point3d b)
{
    Point3d pc = a;
    pc = b;
    b = a;
    return pc;
}

int main()
{
    Point3d pA(1.21,2.32,4.32);

    Point3d pB(0.32,3.32,1.231);
    Point3d pc;

    auto start = std::chrono::steady_clock::now();
    for(int i = 0; i < 10000000; i++)
    {
        pc = Lots_of_copy(pA, pB);
    }
    auto end = std::chrono::steady_clock::now();
    double duration_second = std::chrono::duration<double>(end - start).count();
    cout << "Time cost is: " << duration_second << "seconds" << endl;
    return 0;
}


