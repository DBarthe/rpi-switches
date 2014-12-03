#ifndef INNER_PROFILE_H
#define INNER_PROFILE_H

#include "IProfile.h"
#include "IChooser.h"

class InnerProfile : public IProfile {
private:
  IChooser& _innerChooser;

public:
  InnerProfile(IChooser& chooser)
  : IProfile(), _innerChooser(chooser) {
  }

  virtual ~InnerProfile() {
    delete &_innerChooser;
  }

  virtual std::list<ATask*>&
  innerConsult(std::string const& chanName) const {
    return _innerChooser.consult(chanName);
  }

  virtual std::list<ATask*>&
  outerConsult(std::string const&) const {
    return *new std::list<ATask*>; 
  }
};

#endif // INNER_PROFILE_H
