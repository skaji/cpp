#ifndef FILE_HPP
#define FILE_HPP

#include <string>
#include <sys/stat.h>

class File {
 public:
  File(const std::string& path);
  ~File();
  bool read(std::string& out);
  bool isReplaced() const;
 private:
  std::string path_;
  ino_t inode_;
};

#endif
