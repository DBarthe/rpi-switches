#ifndef MASTER_MULTI_H
#define MASTER_MULTI_H

#include <string>
#include <list>
#include <functional>

#include "AMaster.h"

class MasterMulti : public AMaster {
private:
  std::list<std::string> _chanNameList;

  std::list<ATask*>& _consultHelper(
    // function that takes a chanName and returns a taskList
    std::function<std::list<ATask*>& (std::string const&)> func) const {

    auto& taskList = *new std::list<ATask*>;
    for (auto& chanName : _chanNameList) {
      auto& tmpList = func(chanName);
      taskList.splice(taskList.end(), tmpList);
      delete &tmpList;
    }
    return taskList;
  }

public:
  MasterMulti(IProfile& profile)
  : AMaster(profile), _chanNameList() {}

  MasterMulti(IProfile& profile,
    std::list<std::string>const& chanNameList)
  : AMaster(profile), _chanNameList(chanNameList) {}

  // this ctor causes ambiguity with the previous one.
  // MasterMulti(IProfile& profile,
  //   std::list<std::string const*> chanNameList)
  // : MasterMulti(profile) {
  //   for (auto chanName : chanNameList) {
  //     if (chanName != nullptr) {
  //       add(*chanName);
  //     }
  //   }
  // }

  void add(std::string const& chanName) {
    _chanNameList.push_back(chanName);
  }

  virtual std::list<ATask*>& innerConsult() const {
    return _consultHelper(
      [this](std::string const& chanName) -> std::list<ATask*>& {
        return _profile.innerConsult(chanName);
    });
  }

  virtual std::list<ATask*>& outerConsult() const {
    return _consultHelper(
      [this](std::string const& chanName) -> std::list<ATask*>& {
        return _profile.outerConsult(chanName);
    });
  }  
};

#endif // MASTER_MULTI_H
