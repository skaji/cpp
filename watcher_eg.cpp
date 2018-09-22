#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "watcher/watcher.hpp"
using namespace std;

static void load(const string& path, void* content) {
  ifstream ifs(path);
  ostringstream ss;
  ss << ifs.rdbuf();
  static_cast<string*>(content)->assign(ss.str());
}

class File {
 public:
  File(const string& path) : watcher_(path), content_() {}
  ~File() {}
  bool reload_if_renamed() {
    bool ok = watcher_.if_renamed(load, &content_);
    cout << "[" << content_ << "]\n";
    return ok;
  }
 private:
  Watcher watcher_;
  string content_;
};

int main() {
  File file("hoge.txt");
  while (true) {
    file.reload_if_renamed();
    sleep(5);
  }
  return 0;
}
