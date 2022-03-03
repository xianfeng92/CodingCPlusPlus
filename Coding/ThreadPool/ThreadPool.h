#ifndef CODING_THREADPOOL_THREADPOOL_H_
#define CODING_THREADPOOL_THREADPOOL_H_

#include "SafeQueue.h"

#include <string>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <functional>
#include <future>

class ThreadPool
{
private:
    class ThreadWorker{
        private:
            const char* m_name_;
            ThreadPool* m_pool_;

        public:

            ThreadWorker(ThreadPool* pool,const char* name) : m_pool_(pool), m_name_(name) {
                printf("create%s, %s:++\n",m_name_, __FUNCTION__); 
            }

            void operator()(){
                std::function<void()> func;
                bool dequeued;
                while(!m_pool_->m_shutdown){
                    std::unique_lock<std::mutex> lock(m_pool_->m_condition_mutex);
                    if(m_pool_->m_queue.empty()){
                        m_pool_->m_condition_lock.wait(lock);
                    }
                    dequeued = m_pool_->m_queue.dequeue(func);
                    if(dequeued){
                        func();
                    }
                }
            }

            ~ThreadWorker(){
                printf("destroy %s, %s:--\n",m_name_, __FUNCTION__); 
            }
    };

    bool m_shutdown;
    SafeQueue<std::function<void()>> m_queue;
    std::vector<std::thread> m_threads;
    std::mutex m_condition_mutex;
    std::condition_variable m_condition_lock;
public:
    ThreadPool(const int threads) : m_threads(std::vector<std::thread>(threads)), m_shutdown(false){}

    ThreadPool(const ThreadPool&) = delete;
    ThreadPool(ThreadPool&& ) = delete;
    ThreadPool & operator=(const ThreadPool &&) = delete;
    ThreadPool & operator=(ThreadPool &&) = delete;

    void init(){
        for(int i = 0; i < m_threads.size(); i++){
            // using move assign for std::thread
            m_threads[i] = std::thread(ThreadWorker(this, "Asr"));
        }
    }

    void shutdown(){
        m_shutdown = true;
        m_condition_lock.notify_all();
        for(int i = 0; i < m_threads.size() ; i++){
            if(m_threads[i].joinable()){
                m_threads[i].join();
            }
        }
    }

    template <typename F, typename ... Args>
    auto submit(F&& f, Args && ...args)->std::future<decltype(f(args...))>{
        std::function<decltype(f(args...))()> func = std::bind(std::forward<F>(f), std::forward<Args>(args)...);
        auto task_ptr = std::make_shared<std::packaged_task<decltype(f(args...))()>>(func);

        std::function<void()> wrapper_func = [task_ptr](){
            (*task_ptr)();
        };

        m_queue.enqueue(wrapper_func);
        m_condition_lock.notify_one();
        
        return task_ptr->get_future();
    }

};

#endif // CODING_THREADPOOL_THREADPOOL_H_



























