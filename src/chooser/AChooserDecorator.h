#ifndef ACHOOSERDECORATOR_H_
#define ACHOOSERDECORATOR_H_

#include "IChooser.h"

class AChooserDecorator : public IChooser {
protected:
  IChooser& _chooser;

public:
  AChooserDecorator(IChooser& chooser) : _chooser(chooser) {}

  virtual ~AChooserDecorator() {
    delete &_chooser;
  }

};

#endif // !ACHOOSERDECORATOR_H_