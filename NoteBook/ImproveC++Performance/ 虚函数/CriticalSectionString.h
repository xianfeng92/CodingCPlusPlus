#ifndef CRITICALSECTIONSTRING_H_
#define CRITICALSECTIONSTRING_H_

#include <string>

using std::string;

class CriticalSectionString : public string
{
public:
    ...
    int  length();

private:
    CriticalSectionLock cs;
};

int  CriticalSectionString::length()
{
    cs.lock();
    int len = string.length();
    cs.unlock();
    return len;
}

#endif // CRITICALSECTIONSTRING_H_
