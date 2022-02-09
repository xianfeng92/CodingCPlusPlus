#ifndef SIMPLEMUTEX_H_
#define SIMPLEMUTEX_H_

class SimpleMutex// 版本2，单独的锁类
{
public:
    SimpleMutex(pthread_mutex_t &lock):myLock(lock)
    {
        acquire();
    }
    ~SimpleMutex()
    {
        release();
    }
private:
    int acquire()
    {
        return pthread_mutex_lock(&myLock);
    }

    int release()
    {
        return pthread_mutex_unlock(&myLock);
    }
    pthread_mutex_t &myLock;
};


class BaseMutex 
{
public:
    BaseMutex(pthread_mutex_t &lock){};
    virtual ~BaseMutex(){};
};

class DerivedMutex: public BaseMutex
{
public:
    DerivedMutex(pthread_mutex_t &lock):BaseMutex(lock),myLock(lock)
    {
        acquire();
    }

    ~DerivedMutex()
    {
        release();
    }

private:
    int acquire(){ return pthread_mutex_lock(&myLock);}
    int release(){ return pthread_mutex_unlock(&myLock);}
}

#endif // SIMPLEMUTEX_H_
