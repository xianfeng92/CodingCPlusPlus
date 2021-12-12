#ifndef CIRCLE_H
#define CIRCLE_H

class Circle
{
public:
    Circle()
    {
    }
    ~Circle()
    {
    }
    double area(Radius radius)
    {
        s = radius.r * radius.r * 3.14159;
        return s;
    }

private:
    double s;
};

#endif //