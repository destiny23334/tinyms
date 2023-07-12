//
// Created by zhuka on 2022/9/7.
//

#ifndef TINYMS_INCLUDE_POLL_H_
#define TINYMS_INCLUDE_POLL_H_
#include <vector>
#include <map>
#include <Timestamp.h>
#include <sys/epoll.h>
namespace tinyms {

// 防止循环引用
class Channel;
class EventLoop;

class Poller {
 public:
  using ChannelList = std::vector<Channel *>;
  Poller(EventLoop *loop);
  ~Poller();
  /**
   * Poller的关键，底层是epoll处理事件循环
   */
  Timestamp poll(int timeoutMs, ChannelList* activeChannels);

  /**
   * 更新监听的文件描述符上的事件
   * 这个函数只能被所属的IO线程调用
   */
  void updateChannel(Channel *);
  void assertinLoopThread();
 private:
  using ChannelMap = std::map<int, Channel *>; // fd -> channel的映射
  using PollerFdList = std::vector<epoll_event>;

  /**
   * 这个函数用来找到有事件发生的fd，并将其channel填到activeChannels中
   * TODO: 这个放到后期写，因为需要用epoll
   * @param numEvents 有事件发生的fd数量
   * @param activeChannels
   */
  void fillActiveChannels(int numEvents, ChannelList *activeChannels) const;

  EventLoop *loop_;
  PollerFdList pollerFds_;  // 保存监听的fd的epoll_event
  ChannelMap channels_;

};

}

#endif //TINYMS_INCLUDE_POLL_H_
