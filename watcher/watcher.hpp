#include <string>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

class Watcher {
 public:
  typedef void (*Func)(const std::string& path, void* ptr);
  explicit Watcher(const std::string& path);
  ~Watcher();
  bool if_renamed(Func func, void* ptr = NULL);
 private:
  std::string path_;
  ino_t inode_;
};
