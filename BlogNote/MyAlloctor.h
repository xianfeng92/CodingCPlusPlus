#ifndef BLOGNOTE_MYALLOCTOR_H_
#define BLOGNOTE_MYALLOCTOR_H_

#include <stdlib.h>

#include <iostream>
#include <limits>

template <typename T> class MyAllocator {
public:
  using value_type T;
  using pointer = T *;
  using const_pointer = const T *;
  using void_pointer = void *;
  using const_void_pointer = const void *;
  using size_type = size_t;
  using different_type = std::ptrdiff_t;

  MyAllocator() = default;
  ~MyAllocator() = default;

  pointer allocate(size_t numObjs) {
    return static_cast<pointer>(operator new(sizeof(T) * numObjs));
  }

  pointer allocate(size_t numObjs, const_void_pointer hit) {
    return allocate(numObjs);
  }

  void deallocate(pointer p, size_type numObjs) { operator delete(p); }

  size_type max_size() const { return std::numeric_limits<size_type>::max(); }

  //构造函数
  template <typename U, typename... Args> void constructor(U *p, Args &&...) {
    new (p) U(std::forward<Args>(args)...);
  }

  template <typename U, typename... Args> vod destroy(U *p) { p->~U(); }

  template <typename U> struct rebind {
    using other = MyAllocator<U>;
  }

  size_type
  getAllocatedCount() {
    return alloc_count_;
  }

private:
  size_type alloc_count_;
};

#endif // BLOGNOTE_MYALLOCTOR_H_
