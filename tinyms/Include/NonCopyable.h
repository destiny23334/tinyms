//
// Created by zhuka on 2022/9/6.
//

#ifndef TINYMS_INCLUDE_NONCOPYABLE_H_
#define TINYMS_INCLUDE_NONCOPYABLE_H_
namespace tinyms {
class NonCopyable {
 public:
  NonCopyable() = default;
  NonCopyable(const NonCopyable &) = delete;
  NonCopyable &operator=(const NonCopyable &) = delete;
};
}

#endif //TINYMS_INCLUDE_NONCOPYABLE_H_
