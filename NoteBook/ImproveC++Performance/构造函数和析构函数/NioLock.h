#ifndef NIOLOCK_H_
#define NIOLOCK_H_

class NIOLock
{
public:
    NIOLock(pthread_mutex_t &key):theKey(key)
    {
        pthread_mutex_lock(&theKey);
    }

    ~NIOLock()
    {
        pthread_mutex_unlock(&theKey);
    }
private:
    pthread_mutex_t &theKey;
};

#endif // NIOLOCK_H_
