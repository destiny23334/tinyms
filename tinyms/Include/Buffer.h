#include <unistd.h>

// �����̰߳�ȫ��
// һ��bufferֻӦ�ñ�ͬһ���߳�ʹ��
class Buffer {
 public:
  Buffer(int bufferSize) : buffer_(bufferSize) {}

  // ����
  void read();
  void write();

  // ��ȡ������
  void peek();
 private:
  int r_;
  int w_;
  std::vector<char> buffer_;

};