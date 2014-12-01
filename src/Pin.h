/* 
 * File:   Pin.h
 * Author: barth
 *
 * Created on 30 novembre 2014, 20:29
 */

#ifndef PIN_H
#define	PIN_H

#include "AGpio.h"

class Pin {

  static AGpio& s_gpio;
  int m_num;

public:
  Pin(int num) : m_num(num) {
    s_gpio.init(num);
  }

  Pin(const Pin& orig) : m_num(orig.m_num) {}
  virtual ~Pin() {}

  bool read() const {
    return s_gpio.read(m_num);
  }

  void write(bool value) {
    s_gpio.write(m_num, value);
  }

  int getNum() const {
    return m_num;
  }
};

#endif	/* PIN_H */

