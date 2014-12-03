#ifndef I_MASTER_H
#define I_MASTER_H

#include <list>
#include "ATask.h"

class IMaster {

public:
  virtual ~IMaster() = default;

  virtual std::list<ATask*>& innerConsult() const = 0;
  virtual std::list<ATask*>& outerConsult() const = 0;
};

#endif // I_MASTER_H
