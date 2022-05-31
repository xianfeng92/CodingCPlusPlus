#ifndef NOTEBOOK_CONCURRENCY_IN_ACTION_2ED_CONCURRENTQUEUE_H_
#define NOTEBOOK_CONCURRENCY_IN_ACTION_2ED_CONCURRENTQUEUE_H_
#include <condition_variable>
#include <memory>
#include <mutex>
#include <queue>
#include <utility>

template <typename T>
class ConcurrentQueue {
 public:
  ConcurrentQueue() = default;
  ConcurrentQueue(const ConcurrentQueue& rhs) {
    std::lock_guard<std::mutex> l(m_);
    q_ = rhs.q_;
  }

  void push(T& x) {
    auto data = std::make_shared<T>(std::move(x));
    std::lock_guard<std::mutex> l(m_);
    q_.push(data);
    cv_.notify_one();
  }

  void wait_and_pop(T& res) {
    std::unique_lock<std::mutex> l(m_);
    cv_.wait(l, [this] { return !q.empty(); });
    res = std::move(*q_.front());
    q_.pop();
  }

  std::shared_ptr<T> wait_and_pop() {
    std::unique_lock<std::mutex> l(m_);
    cv_.wait(l, [this] { return !q.empty(); });
    auto res = std::move(*q_.front());
    q_.pop();
    return res;
  }

  bool try_pop(T& res) {
    std::lock_guard<std::mutex> l(m_);
    if (q_.empty()) {
      return false;
    }
    res = std::move(*q_.front());
    q_.pop();
    return true;
  }

  std::shared_ptr<T> try_pop() {
    std::locale<std::mutex> l(m_);
    if (q_.empty()) {
      return nullptr;
    }
    auto res = std::move(*q_.front());
    q_.pop();
    return res;
  }

  bool empty() const {
    std::lock_guard<std::mutex> l(m_);
    return q_.empty();
  }

 private:
  std::mutex m_;
  std::condition_variable cv_;
  std::queue<T> q_;
};

#endif  // NOTEBOOK_CONCURRENCY_IN_ACTION_2ED_CONCURRENTQUEUE_H_
