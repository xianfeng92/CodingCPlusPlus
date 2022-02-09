
int main()// 版本1
{
    ...
    // 开始计时
    for(int i=0; i< 10000, i++)
    {
        pthread_mutex_lock(&theKey);
        ++sharedCounter;
        pthread_mutex_unlock(&theKey);
    }
    // 结束计时
    ...
}

int main()// 版本2
{
    ...
    // 开始计时
    for(int i=0; i< 10000, i++)
    {
        SimpleMutex m(mutex);
        ++sharedCounter;
    }
    // 结束计时
    ...
}

int main()// 版本3
{
    ...
    // 开始计时
    for(int i=0; i< 10000, i++)
    {
        DerivedMutex m(mutex);
        ++sharedCounter;
    }
    // 结束计时
    ...
}


