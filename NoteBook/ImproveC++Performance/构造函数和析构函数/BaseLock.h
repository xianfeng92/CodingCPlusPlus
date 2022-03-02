#ifndef BASELOCK_H_
#define BASELOCK_H_

class BaseLock
{
public:
    // LogSource 对象将在稍后解释
    BaseLock(pthread_mutex_t &key, LogSource &log);

    virtual ~BaseLock(){};
};

#endif // BASELOCK_H_
