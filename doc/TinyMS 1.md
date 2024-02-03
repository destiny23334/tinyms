初步实现Eventloop

## 什么都不做的EventLoop

EventLoop可以理解为一个事件循环类。这个类负责循环监听感兴趣的事件，tinyms采用one loop per thread。

拥有EventLoop的对象的线程叫做IO线程，负责处理IO事件。每个IO线程有且仅有一个EventLoop对象

如何保证一个线程只有一个EventLoop对象？全局变量+__thread。

tinyms用一个全局变量保存当前线程的EventLoop对象。__thread关键字保证了每个线程一个

