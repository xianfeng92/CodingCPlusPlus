#ifndef RADIUS_H
#define RADIUS_H

class Radius
{
    friend class Circle;
    friend void show(Radius &r);

public:
    Radius(int x)
    {
        r = x;
    }

    ~Radius()
    {
    }

private:
    int r;
};

void show(Radius &n)
{
    cout << "Radius is " << n.r << endl;
}

#endif /*