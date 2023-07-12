//
// Created by zhuka on 2022/9/6.
//

#ifndef TINYMS__EVENTLOOP_H_
#define TINYMS__EVENTLOOP_H_
#include <thread>
#include <atomic>
#include <vector>
#include <NonCopyable.h>
namespace tinyms {

// 防止循环引用
class Poller;
class Channel;

class EventLoop : NonCopyable {
 public:
  EventLoop();
  ~EventLoop();

  /**
   * 开启事件循环
   */
  void loop();

  /**
   * 退出事件循环
   * 这个函数是其他线程调用的，比如主线程
   */
  void quit();

  /**
   * 更新监听的fd
   * 本质上是调用epoll来更新
   */
  void updateChannel(Channel *channel);

  /**
   * 如果不是当前，那么
   */
  void assertInLoopThread();

  /**
   * 这里有两种方式
   * 1. 判断EventLoop对象所属的线程ID是否等于当前线程ID
   * 2. 判断当前线程保存的EventLoop是否是this
   * 这里我们使用方式1
   */
  bool isInLoopThread() { return threadId_ == std::this_thread::get_id(); }

  // 上面是获取EventLoop对象所属的ID，这里是获取IO线程的EventLoop对象。显然这应该是个静态函数
  static EventLoop *getEventLoopOfCurrentThread();
 private:
  using ChannelList = std::vector<Channel *>;
  void abortNotInThread();

  Poller *poll_;

  // 因为会在其他线程调用，所以用atomic
  std::atomic<bool> looping_;  // 是否正在进行事件循环
  std::atomic<bool> quit_;

  std::thread::id threadId_;    // 表示EventLoop对象所属的线程id
  ChannelList activeChannels_;  // 记录有事件发生的Channel，由Poller设置
};

} // tinyms

#endif //TINYMS__EVENTLOOP_H_
