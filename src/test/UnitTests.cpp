
#include <iostream>

#include "SimulatedGpio.h"
#include "GpioWrapper.h"

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
  gpio.init(3);
  gpio.write(3, true);
  AGpio& gpio2 = GpioWrapper::unwrap();
  assert(gpio2.read(3) == true);
}


int main() {
  testSimulatedGpio();
  testGpioWrapper();
}
