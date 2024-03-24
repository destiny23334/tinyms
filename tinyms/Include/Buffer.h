#include <unistd.h>

// 不是线程安全的
// 一块buffer只应该被同一个线程使用
class Buffer {
 public:
  Buffer(int bufferSize) : buffer_(bufferSize) {}

  // 消费
  void read();
  void write();

  // 读取不消费
  void peek();
 private:
  int r_;
  int w_;
  std::vector<char> buffer_;

};