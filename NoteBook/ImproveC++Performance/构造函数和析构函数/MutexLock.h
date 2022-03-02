#ifndef MUTEXLOCK_H_
#define MUTEXLOCK_H_

class MutexLock : public BaseLock
{
public:
    MutexLock(pthread_mutex_t &key, LogSource &log);
    ~MutexLock();
private:
    pthread_mutex_t &theKey;
    LogSource &theLog;
};

MutexLock::MutexLock(pthread_mutex_t &key, LogSource &log):BaseLock(key, log),theKey(key),theLog(log)
{
    pthread_mutex_lock(&theKey);
    #if defined(DEBUG)
    cout << "MutexLock" << &theKey << "created at  " << log.file() << "line " << log.line() <<'\n';
    #endif

}

MutexLock::~MutexLock()
{
    pthread_mutex_unlock(&theKey);
     #if defined(DEBUG)
    cout << "MutexLock" << &theKey << "destroyed at  " << log.file() << "line " << log.line() <<'\n';
    #endif
}


#endif // MUTEXLOCK_H_
