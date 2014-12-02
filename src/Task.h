#ifndef TASK_H_
#define TASK_H_

#include <string>

#include "ChannelController.h"

template <bool VALUE>
class Task {
  std::string _chanName;

public:
  Task(std::string const chanName) : _chanName(chanName) {}
  void execute(ChannelController& controller) {
    controller.write(_chanName, VALUE);
  }
};

#endif // !TASK_H_