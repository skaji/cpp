#ifndef FILE_HPP
#define FILE_HPP

#include <string>
#include <sys/stat.h>

class File {
 public:
  File();
  ~File();
  void init(const std::string& path);
  bool read(std::string& out);
  bool isReplaced() const;
 private:
  std::string path_;
  ino_t inode_;
};

#endif
