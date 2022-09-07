//
// Created by zhuka on 2022/9/6.
//

#ifndef TINYMS__EVENTLOOP_H_
#define TINYMS__EVENTLOOP_H_
#include <thread>
#include <NonCopyable.h>
namespace tinyms {

class EventLoop : NonCopyable {
 public:
  EventLoop();
  ~EventLoop();
  void loop();
  void assertInLoopThread();  // 如果不是当前，那么

  // 这里有两种方式
  // 1. 判断EventLoop对象所属的线程ID是否等于当前线程ID
  // 2. 判断当前线程保存的EventLoop是否是this
  // 这里我们使用方式1
  bool isInLoopThread() { return threadId_ == std::this_thread::get_id(); }

  // 上面是获取EventLoop对象所属的ID，这里是获取IO线程的EventLoop对象。显然这应该是个静态函数
  static EventLoop* getEventLoopOfCurrentThread();
 private:
  void abortNotInThread();

  // TODO: 这个looping需要是atomic的吗？
  bool looping_;  // 是否正在进行事件循环
  std::thread::id threadId_;  // 表示EventLoop对象所属的线程id
};

} // tinyms

#endif //TINYMS__EVENTLOOP_H_
