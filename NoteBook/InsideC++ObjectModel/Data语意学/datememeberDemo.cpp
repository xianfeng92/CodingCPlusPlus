#include <iostream>


using namespace std;

class Point3d {
 public:
  Point3d(float x = 0.0f, float y = 0.0f, float z = 0.0f)
      : x_(x), y_(y), z_(z) {}
  virtual ~Point3d();
  //...
 private:
  static Point3d origin;
  float x_, y_, z_;
};


int main()
{
    // cout << "&Point3d::x_" << (int)&Point3d::x_ << endl;
    // cout << "&Point3d::y_" << (int)&Point3d::y_ << endl;
    // cout << "&Point3d::z_" << (int)&Point3d::z_ << endl;

    printf("&Point3d::x_= %p\n", &Point3d::x_);
    printf("&Point3d::y_= %p\n", &Point3d::y_);
    printf("&Point3d::z_= %p\n", &Point3d::z_);
    return 0;
}