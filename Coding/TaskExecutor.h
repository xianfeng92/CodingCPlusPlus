#ifndef CODING_TASKEXECUTOR_H_
#define CODING_TASKEXECUTOR_H_

#include <vector>
#include <queue>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <stdexcept>
#include <unistd.h>

class TaskExecutor
{
public:
    TaskExecutor(size_t);
    template <typename F, typename ...Args>
    auto AddTask(F&& f, Args&& ...args)->std::future<typename std::result_of<F(Args...)>::type;
    ~TaskExecutor();
private:
    //  need to keep track of threads so we can join them
    std::vector<std::thread> works;
    // the task queue
    std::queue<std::function<void()>> tasks;

    // synchronization
    std::mutex queue_mutex;
    std::condition_variable condition;
    bool stop;
};

inline TaskExecutor::TaskExecutor(size_t threads) : stop(false){
    printf("create %s:++\n", __FUNCTION__);
    for(size_t i = 0; i < threads; i++){
        works.emplace([this]{
            for(;;){
                std::function<void()> task;
                {
                    std::unique_lock<std::mutex> lock(this->queueMutex);
                    this.condition.wait(lock, [this]{return this->stop || !this->tasks.empty();});
                    task = std::move(this->tasks.front());
                    this->tasks.pop();
                }
                // run task
                task();
            }
        })
    }
}

template <typename F, typename ... Args>
auto TaskExecutor::AddTask(F&& f, Args&&...args)->std::future<typename std::result_of<F(Args...)>::type>{
    using return_type = typename std::result_of<F(Args...)>::type;
    auto task = std::make_shared<std::packaged_task<return_type>>(std::bind(std::forward<F>(f), std::forward<Args>(args)...));
    
    std::future<return_type> res = task->get_future();
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        if(stop){
            throw std::runtime_error("enqueue on stop task_executor");
        }
        tasks.emplace([task](){(*task)();});
    }
    condition.notify_one();
    return res;
}

TaskExecutor::~TaskExecutor(){
    printf("%s:--\n", __FUNCTION__);
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        stop = true;
    }
    // notify all thread in wait for task
    condition.notify_all();
    for(std::thread &work: workers)
    {
        work.join();
    }
}

#endif // CODING_TASKEXECUTOR_H_
