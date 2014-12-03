#ifndef ICHOOSER_H_
#define ICHOOSER_H_

#include <list>
#include <string>

#include "ATask.h"

class IChooser {
protected:

  static std::list<ATask*>&
  emptyList() {
    auto& list = *new std::list<ATask*>;
    return list;
  }

  // using of decltype for testing purpose
  static auto
  singletonList(ATask* task) -> decltype(emptyList()) {
    auto& list = emptyList();
    list.push_front(task);
    return list;
  }

public:
  virtual ~IChooser() {}

  virtual auto
  consult(std::string const& chanName) const
  -> decltype(emptyList()) = 0;
};


#endif // ICHOOSER_H_