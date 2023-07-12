//
// Created by zhuka on 2022/9/7.
//

#include <Channel.h>
#include <EventLoop.h>

namespace tinyms {

Channel::Channel(EventLoop *loop, int fd)
    : fd_(fd), loop_(loop), events_(0), revents_(0), index_(-1) {

}

void Channel::handleEvent() {
  // TODO: 还没写事件处理
  // 这里只是模拟一下事件处理，后期会改
  if (revents_ & EPOLLIN) {

  }
  if (revents_ & (EPOLLIN | EPOLLPRI | EPOLLHUP)) {

  }
}

void Channel::update() {
  // 用户->Channel->EventLoop->Poller::update
  loop_->updateChannel(this);
}

}
