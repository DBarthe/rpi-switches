#ifndef GPIOWRAPPER_H_
#define GPIOWRAPPER_H_


#ifdef DESKTOP_MODE
 # include "SimulatedGpio.h"
#else
 # include "RpiGpio.h"
#endif // DESKTOP_MODE

/*
 * GpioWrapper is a singleton that wraps the gpio instance.
 *
 * It is used with GpioWrapper::unwrap(), that returns the gpio instance.
 */
class GpioWrapper
{
private:
  IGpio& m_gpio;

#ifdef DESKTOP_MODE
  GpioWrapper() :
    m_gpio(*new SimulatedGpio)
  {}
#else
  GpioWrapper() :
    m_gpio(*new RpiGpio)
  {}
#endif // DESKTOP_MODE

  GpioWrapper(GpioWrapper const&);
  void operator=(GpioWrapper const&);

  ~GpioWrapper() {
    delete &m_gpio;
  }

  static GpioWrapper& getInstance() {
    static GpioWrapper instance;
    return instance;
  }

public:
  static IGpio& unwrap() {
    return getInstance().m_gpio;
  }

};




#endif