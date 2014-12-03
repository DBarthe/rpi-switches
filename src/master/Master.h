#ifndef MASTER_H
#define MASTER_H

#include <string>

#include "AMaster.h"

class Master : public AMaster {

  std::string _chanName;

public:
  Master(IProfile& profile, std::string const& chanName)
  : AMaster(profile), _chanName(chanName) {}

  virtual std::list<ATask*>& innerConsult() const {
    return _profile.innerConsult(_chanName);
  }

  virtual std::list<ATask*>& outerConsult() const {
    return _profile.outerConsult(_chanName);
  }
};

#endif // MASTER_H
