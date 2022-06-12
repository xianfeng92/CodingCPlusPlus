#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <string>
#include <string.h>

static const char *FILE_SRC_PATH = "./hello";

using namespace std;

static void test1() {
  int dir_exists = access(FILE_SRC_PATH, 0);
  if (dir_exists != 0) {
    int ret = mkdir(FILE_SRC_PATH, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    if (ret == 0) {
      std::cout << "mkdir create " << FILE_SRC_PATH << "success " << std::endl;
    } else {
      std::cout << "mkdir create " << FILE_SRC_PATH << "fail, error is " << strerror(errno) << std::endl;
      return;
    }
  } else {
    std::cout << FILE_SRC_PATH << "already exists " << std::endl;
  }
}

int main(int argc, char **argv) {
    test1();
    return 0;
}