#include <string>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

class Watcher {
 public:
  struct Result {
    bool renamed = false;
    int errno = 0;
    std::string error;
  };

  explicit Watcher(const std::string& path);
  ~Watcher();
  Result watch();
 private:
  std::string path_;
  ino_t inode_;
};
