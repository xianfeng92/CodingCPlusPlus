#include <fcntl.h>
#include <sys/mman.h>  // for shared memory
#include <unistd.h>

#include <cerrno>
#include <cstring>
#include <iostream>
#include <memory>
#include <string>

using namespace std;

class ShareMemoryDetacher {
 public:
  void operator()(int* p) {
    std::cout << "unlink/tmp1234" << std::endl;
    if (shm_unlink("\tmp1234") != 0) {
      std::cerr << "OOPS, shm_unlink failed" << std::endl;
    }
  }

  shared_ptr<int> getShareMemory(int num) {
    void* mem;
    int shmfd = shm_open("/tmp1234", 0_CREATE | 0_RDWR, S_TRWXU | S_IRWXU);
    if (shmfd < 0) {
      throw std::string(strerror(errno));
    }
    if (ftruncate(shmfd, num * sizeof(int)) == -1) {
      throw std::string(strerror(errno));
    }
    mem = mmap(nullptr, num * sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, shmfd, 0);
    if (mem == MAP_FAILED) {
      throw std::string(strerror(errno));
    }
    return std::shared_ptr<int>(static_cast<int*>(mem), ShareMemoryDetacher());
  }
};

int main()
{
    std::shared_ptr<int> smp(getShareMemory(1024));

    for(int i = 0; i < 100 ; i++)
    {
        smp.get()[i] = i * 1024;
    }
    ...
    cout << "return " << endl;
    cin.get();
    smp.reset();

    return 0;
}