#ifndef INVERSE_H_
#define INVERSE_H_

#include "IChooser.h"
#include "TaskInverse.h"

class Inverse : public IChooser {
public:
  virtual auto consult(std::string const& chanName) const
  -> decltype(emptyList()) { 
    return singletonList(new TaskInverse(chanName));
  }
};

#endif // !INVERSE_H_