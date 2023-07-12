//
// Created by zhuka on 2022/9/7.
//

#include <Poller.h>
#include <EventLoop.h>
#include <Channel.h>
namespace tinyms {

Poller::Poller(EventLoop *loop) {
  loop_ = loop;
}

Poller::~Poller() {

}

void Poller::updateChannel(Channel *channel) {
  assertinLoopThread();
  //TODO: 这里需要调用epoll_ctl来设置监听事件，后面整完epoll再写
  if (channel->index() < 0) { // -1 表示poller没有监听，需要新增

  } else {  // 修改监听事件

  }

}

void Poller::fillActiveChannels(int numEvents, Poller::ChannelList *activeChannels) const {

}
void Poller::assertinLoopThread() {
  loop_->assertInLoopThread();
}

Timestamp Poller::poll(int timeoutMs, Poller::ChannelList *activeChannels) {
  //epoll_wait();
  return Timestamp::now();
}

}
