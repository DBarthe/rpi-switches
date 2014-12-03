#ifndef A_MASTER_H
#define A_MASTER_H

#include "IMaster.h"
#include "IProfile.h"

class AMaster : public IMaster {
  
protected:
  IProfile& _profile;

public:
  AMaster(IProfile& profile) : _profile(profile) {};

  virtual ~AMaster() {
    delete &_profile;
  }
};

#endif // A_MASTER_H
