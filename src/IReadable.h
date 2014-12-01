#ifndef IREADABLE_H_
#define IREADABLE_H_

class IReadable {

public:
  virtual bool read() const = 0;
};

#endif