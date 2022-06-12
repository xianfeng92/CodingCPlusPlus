#ifndef NOTEBOOK_QNX_TOOLS_ZIP_UTILS_H_
#define NOTEBOOK_QNX_TOOLS_ZIP_UTILS_H_

#include <stdlib.h>

#include <iostream>

namespace ZIP_UTILS {
static int CompressDirectory(const std::string& target_name,
                             const std::string& source_dir) {
  std::string command_tar = "tar -cvf";
  std::string command(command_tar + " " + target_name + " " + source_dir);
  std::cout << "command is " << command << std::endl;
  if (system("ls -li") == 0) {
    std::cout << "tar directory successfully" << std::endl;
    return 0;
  } else {
    std::cout << "tar directory failed" << std::endl;
    return -1;
  }
}

static std::string ExecCmd(std::string cmd) {
  std::string data;
  FILE *stream;
  const int max_buffer = 4096;
  char buffer[max_buffer];
  cmd.append(" 2>&1");

  stream = popen(cmd.c_str(), "r");
  if (stream) {
    while (!feof(stream))
      if (fgets(buffer, max_buffer, stream) != NULL) data.append(buffer);
    pclose(stream);
  }
  return data;
}
}  // namespace ZIP_UTILS

#endif  // NOTEBOOK_QNX_TOOLS_ZIP_UTILS_H_
