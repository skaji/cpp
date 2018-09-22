#include <iostream>
#include <string>
#include "watcher/watcher.hpp"
using namespace std;

void load(const string& path) {
  cout << "load!\n";
}

int main() {
  Watcher watcher("README.md");
  while (true) {
    watcher.if_renamed(load);
    sleep(1);
  }
  return 0;
}
