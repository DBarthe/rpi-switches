#ifndef TASKINVERSE_H_
#define TASKINVERSE_H_

#include "ATask.h"

class TaskInverse : public ATask {
public:
  TaskInverse(std::string const chanName) : ATask(chanName) {}

  void execute(ChannelController& controller) const {
    bool value = controller.read(_chanName) ? false : true;
    controller.write(_chanName, value);
  }
};

#endif // !TASKINVERSE_H_