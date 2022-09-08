//
// Created by zhuka on 2022/9/7.
//

#ifndef TINYMS_INCLUDE_CHANNEL_H_
#define TINYMS_INCLUDE_CHANNEL_H_
#include <NonCopyable.h>
#include <functional>
#include <sys/epoll.h>

namespace tinyms {

enum PollerEvent : int {
  NoneEvent = 0,
  ReadEvent = EPOLLIN | EPOLLPRI, // 可读或者紧急数据可读
  WriteEvent = EPOLLOUT
};

class EventLoop;  // 防止循环引用

/**
 * 不用考虑线程安全问题，因为所有成员都在IO线程中调用，没有造成竞争
 */
class Channel : NonCopyable {
 public:
  using EventCallback = std::function<void()>;

  Channel(EventLoop *loop, int fd);

  /**
   * Channel的核心，由EventLoop调用，负责处理事件
   */
  void handleEvent();

  void setReadCallback(const EventCallback &cb) { readCallback_ = cb; }
  void setWriteCallback(const EventCallback &cb) { writeCallback_ = cb; }
  void setErrorCallback(const EventCallback &cb) { errorCallback_ = cb; }

  int fd() const { return fd_; }
  int index() const { return index_; }
  int events() const { return events_; }
  void setRevents(int revents) { revents_ = revents; }

  // 设置监听的事件
  void enableReading() {
    events_ |= PollerEvent::ReadEvent;
    update();
  }
  void enableWriting() {
    events_ |= PollerEvent::WriteEvent;
    update();
  }
  void disableAll() {
    events_ = PollerEvent::NoneEvent;
    update();
  }
  void disableWriting() {
    events_ &= ~(PollerEvent::WriteEvent);
    update();
  }

  EventLoop *ownerLoop() {
    return loop_;
  }

 private:
  void update();  // 让EventLoop监听

  EventLoop *loop_; // channel需要获取到所属的EventLoop，为了修改事件
  const int fd_;
  int events_;  // 记录当前监听的事件，由用户设置
  int revents_; // 记录当前发生的事件，由EventLoop/Poller设置
  int index_; // 标识在Poller中保存的下标，方便poller以O(1)的时间获取channel

  EventCallback readCallback_;
  EventCallback writeCallback_;
  EventCallback errorCallback_;

};

}

#endif //TINYMS_INCLUDE_CHANNEL_H_
