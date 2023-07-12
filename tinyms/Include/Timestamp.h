//
// Created by zhuka on 2022/9/8.
//

#ifndef TINYMS_INCLUDE_TIME_H_
#define TINYMS_INCLUDE_TIME_H_

namespace tinyms
{

/**
 * 时间戳类
 * TODO: 实现时间戳，这个放到定时器的时候实现
 */
struct Timestamp {
  Timestamp() {}
  static Timestamp now() {
    return Timestamp();
  }
};

}

#endif //TINYMS_INCLUDE_TIME_H_
