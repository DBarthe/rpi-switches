
#include <iostream>

#include "SimulatedGpio.h"
#include "GpioWrapper.h"
#include "Pin.h"
#include "Channel.h"
#include "ChannelGroup.h"

void testSimulatedGpio() {

  std::cout << "Testing SimulatedGpio" << std::endl; 

  SimulatedGpio gpio;
  
  gpio.init(21);
  assert (gpio.read(21) == false);
  gpio.write(21, true);
  assert (gpio.read(21) == true);

  gpio.init(6);
  assert (gpio.read(6) == false);
  gpio.write(6, true);
  assert (gpio.read(6) == true);
  gpio.write(6, false);
  assert (gpio.read(6) == false);

  SimulatedGpio gpio2(gpio);
  assert (gpio2.read(21) == true);
  assert (gpio2.read(6) == false);
}

void testGpioWrapper() {
  std::cout << "Testing GpioWrapper" << std::endl; 

  AGpio& gpio = GpioWrapper::unwrap();
  gpio.init(5);
  gpio.write(5, true);
  AGpio& gpio2 = GpioWrapper::unwrap();
  assert(gpio2.read(5) == true);

  gpio.reset();
}

void testPin() {
  std::cout << "Testing Pin" << std::endl; 

  Pin pin(1);
  assert(pin.getNum() == 1);
  pin.write(true);
  assert(pin.read() == true);
  Pin pin2(pin);
  assert(pin2.read() == true);

  GpioWrapper::unwrap().reset();
}

void testChannel() {
  std::cout << "Testing Channel" << std::endl; 

  Pin pin(3);
  pin.write(true);
  Channel channel("foo", pin);
  assert (channel.read() == true);
  channel.write(false);
  assert (channel.read() == false);
  assert (pin.read() == false);
  pin.write(true);
  assert (channel.read() == false);
  channel.sync();
  assert (channel.read() == true);

  GpioWrapper::unwrap().reset();
}

void testChannelGroup() {
  std::cout << "Testing ChannelGroup" << std::endl; 

  Pin pin1(1);
  Pin pin2(2);
  Pin pin3(3);
  Pin pin4(4);

  ChannelGroup::SharedChannel shch1(new Channel("foo", pin1));
  ChannelGroup::SharedChannel shch2(new Channel("bar", pin2));
  ChannelGroup::SharedChannel shch3(new Channel("fish", pin3));
  ChannelGroup::SharedChannel shch4(new Channel("hugs", pin4));

  ChannelGroup cg("group");
  cg.add(shch1);
  cg.add(shch2);
  cg.add(shch3);
  cg.add(shch4);

  cg.write(true);
  assert(shch1->read() == true);
  assert(shch2->read() == true);
  assert(shch3->read() == true);
  assert(shch4->read() == true);

  cg.remove("bar");
  cg.write(false);
  assert(shch1->read() == false);
  assert(shch2->read() == true);
  assert(shch3->read() == false);
  assert(shch4->read() == false);

  cg.forEach([](ChannelGroup::SharedChannel const&shch) {
    shch->write(true);
  });
  assert(shch1->read() == true);
  assert(shch2->read() == true);
  assert(shch3->read() == true);
  assert(shch4->read() == true);

  shch1->write(false);
  cg.removeIf([](ChannelGroup::SharedChannel const& shch) {
    return shch->read() == false;
  });
  cg.write(true);
  assert(shch1->read() == false);
  assert(shch2->read() == true);
  assert(shch3->read() == true);
  assert(shch4->read() == true);

  GpioWrapper::unwrap().reset();
}

int main() {
  testSimulatedGpio();
  testGpioWrapper();
  testPin();
  testChannel();
  testChannelGroup();
}
