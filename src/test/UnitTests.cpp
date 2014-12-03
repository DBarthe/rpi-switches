
#include <iostream>
#include <list>

#include "SimulatedGpio.h"
#include "GpioWrapper.h"
#include "Pin.h"
#include "Channel.h"
#include "ChannelGroup.h"
#include "ChannelController.h"
#include "TaskTurn.h"
#include "TaskInverse.h"
#include "IChooser.h"
#include "Turn.h"
#include "Inverse.h"
#include "ChooserDecoratorMaybe.h"
#include "IProfile.h"
#include "InnerProfile.h"
#include "BifaceProfile.h"
#include "IMaster.h"
#include "AMaster.h"
#include "Master.h"
#include "MasterMulti.h"
#include "MasterComposite.h"


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

  IGpio& gpio = GpioWrapper::unwrap();
  gpio.init(5);
  gpio.write(5, true);
  IGpio& gpio2 = GpioWrapper::unwrap();
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

void testChannelController() {
  std::cout << "Testing ChannelController" << std::endl; 



  Pin pins[6] = {
    Pin(0), Pin(1), Pin(2),
    Pin(3), Pin(4), Pin(5)
  };

  Channel* chans[6] = {nullptr};
  for (int i = 0; i < 6; i++) {
    chans[i] = new Channel("ch"+std::to_string(i), pins[i]);
  }

  // initializer_list and add
  ChannelController cc = {
    chans[0], chans[1], chans[2],
    chans[3], chans[4], chans[5]
  };

  // write and read
  for (auto chan : chans) {
    cc.write(chan->getName(), true);
    assert(chan->read() == true);
    assert(cc.read(chan->getName()) == true);
    chan->write(false);
    assert(cc.read(chan->getName()) == false);
  }

  // sync
  pins[0].write(true);
  assert(cc.read(chans[0]->getName()) == false);
  cc.sync(chans[0]->getName());
  assert(cc.read(chans[0]->getName()) == true);

  // writeAll
  cc.writeAll(true);
  for (auto chan : chans) {
    assert(chan->read() == true);
  }

  // syncAll
  for (auto& p : pins) {
    p.write(false);
  }
  for (auto chan : chans) {
    assert(chan->read() == true);
  }
  cc.syncAll();
  for (auto chan : chans) {
    assert(chan->read() == false);
  }

  // readAll
  auto& map = cc.readAll();
  for (auto& pair : map) {
    assert (cc.read(pair.first) == pair.second);
  }
  delete &map;


  // remove
  std::string savedName = chans[0]->getName();
  cc.remove(savedName);
  cc.writeAll(true);
  assert(pins[0].read() == false);
  try {
    (void)cc.write(savedName, true);
    assert(false);
  } catch (std::exception _) {
    assert(true);
  }

  GpioWrapper::unwrap().reset();
}

void testTask() {
  std::cout << "Testing Task" << std::endl; 

  Pin p(1);
  ChannelController cc;
  cc.add(*new Channel("foo", p));
  cc.write("foo", false);
  auto t = TaskTurn<true>("foo");
  t.execute(cc);
  assert(cc.read("foo") == true);
  auto t2 = TaskInverse("foo");
  t2.execute(cc);
  assert(cc.read("foo") == false);
  t2.execute(cc);
  assert(cc.read("foo") == true);

  GpioWrapper::unwrap().reset();
}


static void
consumeTaskList(std::list<ATask*>& list, ChannelController &cc) {
  for (auto t : list) {
    t->execute(cc);
    delete t;
  }
  delete &list;
}

void testChooser() {
  std::cout << "Testing Chooser" << std::endl; 

  ChannelController cc;
  Pin p(1);
  cc.add(*new Channel("foo", p));
  cc.write("foo", true);

  IChooser& turnOn = *new TurnOn;
  IChooser& turnOff = *new TurnOff;
  IChooser& inverse = *new Inverse;
  IChooser& ifOnOff = *new ChooserDecoratorIfOn(*new TurnOff, cc);
  IChooser& ifOffInverse = *new ChooserDecoratorIfOff(*new Inverse, cc);

  consumeTaskList(turnOff.consult("foo"), cc);
  assert(cc.read("foo") == false);

  consumeTaskList(turnOn.consult("foo"), cc);
  assert(cc.read("foo") == true);

  consumeTaskList(inverse.consult("foo"), cc);
  assert(cc.read("foo") == false);
  consumeTaskList(inverse.consult("foo"), cc);
  assert(cc.read("foo") == true);

  consumeTaskList(ifOnOff.consult("foo"), cc);
  assert(cc.read("foo") == false);
  consumeTaskList(ifOnOff.consult("foo"), cc);
  assert(cc.read("foo") == false);

  consumeTaskList(ifOffInverse.consult("foo"), cc);
  assert(cc.read("foo") == true);
  consumeTaskList(ifOffInverse.consult("foo"), cc);
  assert(cc.read("foo") == true);

  delete &turnOn;
  delete &turnOff;
  delete &inverse;
  delete &ifOnOff;
  delete &ifOffInverse;

  GpioWrapper::unwrap().reset();
}

void testProfile() {
  std::cout << "Testing Profile" << std::endl; 

  ChannelController cc;
  Pin p(1);
  cc.add(*new Channel("foo", p));

  IProfile& inner = *new InnerProfile(*new TurnOn);
  IProfile& biface = *new BifaceProfile(*new TurnOn, *new TurnOff);

  cc.write("foo", false);
  consumeTaskList(inner.outerConsult("foo"), cc);
  assert(cc.read("foo") == false);
  consumeTaskList(inner.innerConsult("foo"), cc);
  assert(cc.read("foo") == true);

  cc.write("foo", false);
  consumeTaskList(biface.outerConsult("foo"), cc);
  assert(cc.read("foo") == false);
  consumeTaskList(biface.innerConsult("foo"), cc);
  assert(cc.read("foo") == true);
  consumeTaskList(biface.outerConsult("foo"), cc);
  assert(cc.read("foo") == false);

  delete &inner;
  delete &biface;

  GpioWrapper::unwrap().reset();
}

void testMaster() {
  std::cout << "Testing Master" << std::endl; 

  Pin p1(1), p2(2), p3(3), p4(4);
  ChannelController cc = {
    new Channel("foo", p1),
    new Channel("bar", p2),
    new Channel("tom", p3),
    new Channel("jerry", p4),
  };

  IMaster& master =
    *new Master(*new InnerProfile(*new Inverse), "foo");
  cc.writeAll(false);
  consumeTaskList(master.innerConsult(), cc);
  assert(cc.read("foo") == true);
  consumeTaskList(master.outerConsult(), cc);
  assert(cc.read("foo") == true);

  IMaster& masterMulti =
    *new MasterMulti(*new InnerProfile(*new Inverse),
      { "foo", "bar", "jerry" });
  cc.writeAll(false);
  consumeTaskList(masterMulti.innerConsult(), cc);
  assert(cc.read("foo") == true);
  assert(cc.read("bar") == true);
  assert(cc.read("tom") == false);
  assert(cc.read("jerry") == true);
  consumeTaskList(masterMulti.outerConsult(), cc);
  assert(cc.read("foo") == true);
  assert(cc.read("bar") == true);
  assert(cc.read("tom") == false);
  assert(cc.read("jerry") == true);

  auto& masterComposite = *new MasterComposite {
    new Master(*new InnerProfile(*new Inverse), "foo"),
    new Master(*new BifaceProfile(*new Inverse, *new TurnOff), "bar"),
    new MasterMulti(*new InnerProfile(*new TurnOn), {"tom", "jerry"})
  };
  cc.writeAll(false);
  consumeTaskList(masterComposite.innerConsult(), cc);
  assert(cc.read("foo") == true);
  assert(cc.read("bar") == true);
  assert(cc.read("tom") == true);
  assert(cc.read("jerry") == true);
  consumeTaskList(masterComposite.outerConsult(), cc);
  assert(cc.read("foo") == true);
  assert(cc.read("bar") == false);
  assert(cc.read("tom") == true);
  assert(cc.read("jerry") == true);

  delete &master;
  delete &masterMulti;
  delete &masterComposite;

  GpioWrapper::unwrap().reset();
}


int main() {
  testSimulatedGpio();
  testGpioWrapper();
  testPin();
  testChannel();
  testChannelGroup();
  testChannelController();
  testTask();
  testChooser();
  testProfile();
  testMaster();

  return 0;
}
