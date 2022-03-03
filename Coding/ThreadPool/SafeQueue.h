#ifndef CODING_THREADPOOL_SAFEQUEUE_H_
#define CODING_THREADPOOL_SAFEQUEUE_H_

#include <mutex>
#include <queue>

template<typename T>
class SafeQueue
{
private:
    std::queue<T> m_queue;
    std::mutex m_mutex;

public:
    SafeQueue(){}

    SafeQueue(SafeQueue&& other){
        //Todo
    }
    ~SafeQueue(){}

    bool empty(){
        std::unique_lock<std::mutex> lock(m_mutex);
        return m_queue.empty();
    }

    bool size(){
        std::unique_lock<std::mutex> lock(m_mutex);
        return m_queue.size();
    }

    void enqueue(T& t){
        std::unique_lock<std::mutex> lock(m_mutex);
        m_queue.push(t);
    }

    bool dequeue(T& t){
        std::unique_lock<std::mutex> lock(m_mutex);
        if(m_queue.empty()){return false;}
        t = std::move(m_queue.front());
        m_queue.pop();
        return true;
    }

};

#endif // CODING_THREADPOOL_SAFEQUEUE_H_
