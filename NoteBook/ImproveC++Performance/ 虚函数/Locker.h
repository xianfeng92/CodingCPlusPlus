#ifndef LOCKER_H_
#define LOCKER_H_

class Locker
{
public:
    Locker();
    virtual ~Locker();
    virtual void lock() = 0;
    virtual void unlock() = 0;
};

#endif // LOCKER_H_
