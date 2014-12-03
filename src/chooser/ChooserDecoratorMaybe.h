#ifndef CHOOSER_DECORATOR_MAYBE_H
#define CHOOSER_DECORATOR_MAYBE_H

#include "AChooserDecorator.h"
#include "ChannelController.h"

template <bool VALUE>
class ChooserDecoratorMaybe : public AChooserDecorator {
  ChannelController const& _controller;

public:
  ChooserDecoratorMaybe(
    IChooser& chooser,
    ChannelController const& controller)
  : AChooserDecorator(chooser), _controller(controller) {
  }

  virtual auto consult(std::string const& chanName) const
  -> decltype(emptyList()) {
    if (_controller.read(chanName) == VALUE) {
        return _chooser.consult(chanName);
    }
    else {
      return emptyList();
    }
  }
};

typedef ChooserDecoratorMaybe<true> ChooserDecoratorIfOn;
typedef ChooserDecoratorMaybe<false> ChooserDecoratorIfOff;

#endif // CHOOSER_DECORATOR_MAYBE_H
