#ifndef BEAR_H_
#define BEAR_H_

class Bear: public ZooAnimal
{
public:
    Bear(const char *name):myName(name),myType(BEAR){ }
    void draw() override;
    ...
};

#endif // BEAR_H_
