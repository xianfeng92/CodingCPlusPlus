#ifndef THREADSAFESTRING_H_
#define THREADSAFESTRING_H_
#include<string>

using std::string;

class ThreadSafeString : public string 
{
public:
    ThreadSafeString(const char* s, Locker *lockPtr):string(s), pLock(lockPtr){}
    ...
    int length();

private:
    Locker *pLock;
}


int ThreadSafeString::length()
{
    pLock->lock();
    int len = string::length();
    pLock->unlock();
    return len;
}

#endif // THREADSAFESTRING_H_
