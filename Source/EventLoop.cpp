//
// Created by zhuka on 2022/9/6.
//
#include <cassert>
#include <iostream>
#include <EventLoop.h>
#include <Poller.h>
#include <Channel.h>

namespace tinyms {

// 注意这个全局变量是线程安全的，因为每个线程都只会访问自己的那个变量
__thread EventLoop *loopInThisThread = nullptr; // 当前线程的EventLoop对象

EventLoop::EventLoop() :
    looping_(false), quit_(false),
    threadId_(std::this_thread::get_id()), poll_(nullptr) {
  if (loopInThisThread) { // 当前线程已经有了
    // log报错
    std::cout << "EventLoop Create Fail! An EventLoop has been Created!\n";
  } else {
    loopInThisThread = this;
  }
}

void EventLoop::assertInLoopThread() {
  if (!isInLoopThread()) {
    abortNotInThread();
  }
}

EventLoop::~EventLoop() {
  assert(!looping_);
  loopInThisThread = nullptr;
}

void EventLoop::loop() {
  // 只有EventLoop对象所属的那个线程才能开启事件循环
  assert(!looping_);
  assertInLoopThread();
  looping_ = true;
  quit_ = false;

  while (quit_) {
    poll_->poll(100, &activeChannels_);
    for (auto channel : activeChannels_) {
      channel->handleEvent();
    }
  }

  looping_ = false;
}

// TODO: 当发现不是所属的IO线程使用我的时候，我该怎么退出？
void EventLoop::abortNotInThread() {

}
EventLoop *EventLoop::getEventLoopOfCurrentThread() {
  return loopInThisThread;
}

void EventLoop::updateChannel(Channel *channel) {
  poll_->updateChannel(channel);
}

void EventLoop::quit() {
  quit_ = true;
  // TODO: wakeup() 实现一个事件能出发poller！！
}

}
