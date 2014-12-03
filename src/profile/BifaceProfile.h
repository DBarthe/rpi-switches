#ifndef BIFACE_PROFILE_H
#define BIFACE_PROFILE_H

#include "InnerProfile.h"

class BifaceProfile : public InnerProfile {
  IChooser& _outer;

public:
  BifaceProfile(IChooser& inner, IChooser& outer)
  : InnerProfile(inner), _outer(outer) {
  }

  virtual ~BifaceProfile() {
    delete &_outer;
  }

  virtual std::list<ATask*>&
  outerConsult(std::string const& chanName) const {
    return _outer.consult(chanName);
  }
};

#endif // BIFACE_PROFILE_H
