#include "file.hpp"

#include <fstream>
#include <sstream>

#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <fcntl.h>

using namespace std;

namespace {
bool slurp(int fd, string& out) {
  char buf[4096];
  ostringstream ss;
  while (1) {
    ssize_t len = read(fd, buf, sizeof(buf));
    if (len < 0) {
      return false;
    } else if (len == 0) {
      out.assign(ss.str());
      return true;
    } else {
      ss.write(buf, len);
    }
  }
}

ino_t getInode(int fd) {
  struct stat buf;
  return fstat(fd, &buf) == 0 ? buf.st_ino : 0;
}

ino_t getInode(const string& path) {
  struct stat buf;
  return stat(path.c_str(), &buf) == 0 ? buf.st_ino : 0;
}
};

File::File(const string& path) : path_(path), inode_(0) {}

File::~File() {}

bool File::read(string& out) {
  int fd = open(path_.c_str(), O_RDONLY);
  if (fd < 0) {
    return false;
  }
  bool ok = slurp(fd, out);
  if (ok) {
    inode_ = getInode(fd);
  }
  close(fd);
  return ok;
}

bool File::isReplaced() const {
  if (inode_ == 0) {
    return true;
  }
  return inode_ != getInode(path_);
}
