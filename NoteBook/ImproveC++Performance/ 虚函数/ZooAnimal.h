#ifndef ZOOANIMAL_H_
#define ZOOANIMAL_H_

class ZooAnimal
{
public:
    ...
    virtual void draw();
    int resolveType() {return myType;}
private:
    int myType;
    ...
};

#endif // ZOOANIMAL_H_
