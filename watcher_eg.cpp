#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <json/json.h>
#include "watcher/watcher.hpp"
using namespace std;

#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

static void load(const string& path, void* out) {
  ifstream ifs(path);
  if (!ifs) {
    cout << "err!\n";
    return;
  }
  ostringstream ss;
  ss << ifs.rdbuf();
  Json::Value root;
  if (!Json::Reader().parse(ss.str(), root)) {
    return;
  }
  if (!root.isObject()) {
    return;
  }
  map<string, string> m;
  for (Json::Value::const_iterator it = root.begin(); it != root.end(); ++it) {
    if (it->isString()) {
      m[it.key().asString()] = it->asString();
    } else {
      return;
    }
  }
  *static_cast<map<string, string>*>(out) = m;
}

class File {
 public:
  File(const string& path) : watcher_(path), content_() {}
  ~File() {}
  bool reload_if_renamed() {
    return watcher_.if_renamed(load, &content_);
  }
  void dump() {
    cout << "------- dump\n";
    for (map<string, string>::const_iterator it = content_.begin(); it != content_.end(); ++it) {
      cout << it->first << ": " << it->second << "\n";
    }
  }
 private:
  Watcher watcher_;
  map<string, string> content_;
};

int main() {
  File file("hoge.json");
  while (true) {
    file.reload_if_renamed();
    file.dump();
    sleep(5);
  }
  return 0;
}
