//
// Created by zhuka on 2022/9/6.
//
#include "EventLoop.h"

// 一个线程无法启动两个eventloop
void twoEventLoopTest() {
  tinyms::EventLoop loop1{};
  tinyms::EventLoop loop2{};
}

void

int main() {
  twoEventLoopTest();
}