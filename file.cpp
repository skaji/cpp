#include "file.hpp"

#include <fstream>
#include <sstream>

using namespace std;

namespace {
ino_t getInode(const string& path) {
  struct stat buf;
  if (stat(path.c_str(), &buf) == 0) {
    return buf.st_ino;
  } else {
    return 0;
  }
}
};

File::File() : path_(), inode_(0) {}

File::~File() {}

void File::init(const string& path) {
  path_ = path;
}

bool File::read(string& out) {
  ifstream in(path_);
  if (!in) {
    return false;
  }
  ostringstream ss;
  ss << in.rdbuf();
  in.close();
  out.assign(ss.str());
  inode_ = getInode(path_);
  return true;
}

bool File::isReplaced() const {
  if (inode_ == 0) {
    return true;
  }
  return getInode(path_) != inode_;
}
