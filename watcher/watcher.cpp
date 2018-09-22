#include "watcher.hpp"

using namespace std;

Watcher::Watcher(const string& path) : path_(path), inode_(-1) {}
Watcher::~Watcher() {}

bool Watcher::if_renamed(Func func, void* ptr) {
  struct stat st;
  int ret = stat(path_.c_str(), &st);
  if (ret == -1) {
    return false;
  }
  if (inode_ == st.st_ino) {
    return true;
  }
  inode_ = st.st_ino;
  func(path_, ptr);
  return true;
}
