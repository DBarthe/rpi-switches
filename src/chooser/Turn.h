#ifndef TURN_H_
#define TURN_H_

#include "IChooser.h"
#include "TaskTurn.h"

template <bool VALUE>
class Turn : public IChooser {

public:
  virtual auto consult(std::string const& chanName) const
  -> decltype(emptyList()) { 
    return singletonList(new TaskTurn<VALUE>(chanName));
  }
};

typedef Turn<true> TurnOn;
typedef Turn<false> TurnOff;

#endif // !TURN_H_