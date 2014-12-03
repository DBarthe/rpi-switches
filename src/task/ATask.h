#ifndef ATASK_H_
#define ATASK_H_

#include <string>

#include "ChannelController.h"

class ATask {
protected:
  std::string _chanName;

public:
  ATask(std::string const chanName) : _chanName(chanName) {}
  virtual ~ATask() {}

  std::string const& getChanName() { return _chanName; }

  virtual void execute(ChannelController& controller) const = 0;
};

#endif // !ATASK_H_