#ifndef TASKTURN_H_
#define TASKTURN_H_

#include "ATask.h"
#include "ChannelController.h"

template <bool VALUE>
class TaskTurn : public ATask {
public:
  TaskTurn(std::string const chanName) : ATask(chanName) {}

  void execute(ChannelController& controller) const {
    controller.write(_chanName, VALUE);
  }
};

#endif // !TASKTURN_H_