#include "watcher.hpp"
#include <stdio.h>
#include <errno.h>
#include <string.h>

using namespace std;

Watcher::Watcher(const string& path) : path_(path), inode_(-1) {}
Watcher::~Watcher() {}

Watcher::Result Watcher::watch() {
  struct stat st;
  int ret = stat(path_.c_str(), &st);
  if (ret == -1) {
    return Result{false, strerror(errno)};
  }
  if (inode_ == st.st_ino) {
    return Result{false};
  }
  inode_ = st.st_ino;
  return Result{true};
}
