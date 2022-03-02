#ifndef ALGORITHM_CIRCULARBUFFER_H_
#define ALGORITHM_CIRCULARBUFFER_H_

class CircularBuffer {
 public:

  explict CircularBuffer(size_t capacity);

  CircularBuffer(CircularBuffer &&) = delete;
  CircularBuffer &operator=(CircularBuffer &&) = delete;
  CircularBuffer(const CircularBuffer &) = delete;
  CircularBuffer &operator=(const CircularBuffer &) = delete;

  ~CircularBuffer();

  /**
   * \brief 获取缓冲区已用大小
   */
  size_t size() const { return size_; }

  /**
   * \brief 获取缓冲区容量
   */
  size_t capacity() const { return capacity_; }

  /**
   * \brief 写入数据
   * \param data 要写入的数据
   * \param bytes 要写入的数据的大小
   * \return 最终写入的数据的大小
   */
  size_t write(const char *data, const size_t bytes);

  /**
   * \brief 读取数据
   * \param data 用来存放读取数据的buffer
   * \param bytes 要读取的数据大小
   * \return 最终获取到的数据的大小
   */
  size_t read(char *data, const size_t bytes);

 private:
  size_t beg_index_, end_index_, size_, capacity_;
  char *data_;
  mutable spin_mutex mut_;
  mutable std::mutex mut_read_;
  mutable std::mutex mut_write_;
};

CircularBuffer::CircularBuffer(size_t capacity)
    : beg_index_(0), end_index_(0), size_(0), capacity_(capacity) {
  data_ = new char[capacity];
}

CircularBuffer::~CircularBuffer() { delete[] data_; }

size_t CircularBuffer::write(const char *data, const size_t bytes) {
  if (bytes == 0) return 0;
  // 通过互斥量保证任意时刻，至多只有一个线程在写数据
  std::lock_guard<std::mutex>lk_write(mut_write_);
  const size_t capacity = capacity_;
  const size_t bytes_to_write = std::min(bytes, capacity - size_);

  if (bytes_to_write <= capacity - end_index_)
  {
    memcpy(data_ + end_index_, data, bytes_to_write);
    end_index_ += bytes_to_write;
    if (end_index_ == capacity) end_index_ = 0;
  }
  else
  {
    size_t size1 = capacity - end_index_;
    memcpy(data + end_index_, data, size1);
    size_t size2 = bytes_to_write - size1;
    memcpy(data, data + size1, size2);
    end_index_ = size2;
  }
  // 通过自旋锁保证任意时刻，至多只有一个线程在改变 size_ .
  std::lock_guard<spin_mutex>lk(mut_);
  size_ += bytes_to_write;
  return bytes_to_write;
}

size_t CircularBuffer::read(char *data, size_t bytes) {
  if (bytes == 0) return 0;

  // 通过互斥量保证任意时刻，至多只有一个线程在读数据
  std::lock_guard<std::mutex>lk_read(mut_read_);
  size_t capacity = capacity_;
  size_t bytes_to_read = std::min(bytes, size_);

  if (bytes_to_read < capacity - beg_index_) {
    memcpy(data, data_ + beg_index_, bytes_to_read);
    if (beg_index_ == capacity) beg_index_ = 0;
  } else {
    size_t size_1 = capacity - beg_index_;
    memcpy(data, data_ + beg_index_, size_1);
    size_t size_2 = bytes_to_read - size_1;
    memcpy(data + size_1, data_, size_2);
    beg_index_ = size_2;
  }

  // 通过自旋锁保证任意时刻，至多只有一个线程在改变 size_ 
  std::lock_guard<spin_mutex>lk(mut_);
  size_ -= bytes_to_read;
  return bytes_to_read;
}

#endif  // ALGORITHM_CIRCULARBUFFER_H_
