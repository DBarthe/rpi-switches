#ifndef MASTER_COMPOSITE_H
#define MASTER_COMPOSITE_H

#include <list>
#include <initializer_list>
#include <functional>

#include "IMaster.h"


class MasterComposite : IMaster {

  std::list<IMaster*> _childrenList;

  std::list<ATask*>& _consultHelper(
    // function that takes a IMaster& and returns a taskList
    std::function<std::list<ATask*>& (IMaster&)> func) const {

    auto& taskList = *new std::list<ATask*>;
    for (auto children : _childrenList) {
      auto& tmpList = func(*children);
      taskList.splice(taskList.end(), tmpList);
      delete &tmpList;
    }
    return taskList;
  }

public:
  MasterComposite() = default;
  MasterComposite(std::initializer_list<IMaster*> childrenList)
  : IMaster(), _childrenList(childrenList) {}
  MasterComposite(std::list<IMaster*> childrenList)
  : IMaster(), _childrenList(childrenList) {}


  virtual ~MasterComposite() {
    for (auto children : _childrenList) {
      delete children;
    }
  }

  void add(IMaster& master) {
    _childrenList.push_back(&master);
  }

  virtual std::list<ATask*>& innerConsult() const {
    return _consultHelper(
      [](IMaster& master) -> std::list<ATask*>& {
        return master.innerConsult();
      });
  }

  virtual std::list<ATask*>& outerConsult() const {
    return _consultHelper(
      [](IMaster& master) -> std::list<ATask*>& {
        return master.outerConsult();
      });
  }
};

#endif // MASTER_COMPOSITE_H
