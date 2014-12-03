#ifndef I_PROFILE_H
#define I_PROFILE_H

#include <list>

#include "ATask.h"

class IProfile {
public:
  virtual ~IProfile() {} ;

  virtual std::list<ATask*>&
  innerConsult(std::string const& chanName) const = 0;
  virtual std::list<ATask*>&
  outerConsult(std::string const& chanName) const = 0;
};

#endif // I_PROFILE_H
