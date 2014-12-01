/* 
 * File:   Channel.h
 * Author: barth
 *
 * Created on 30 novembre 2014, 20:37
 */

#ifndef CHANNEL_H
#define	CHANNEL_H

#include "AChannel.h"
#include "Pin.h"

class Channel : public AChannel {

  Pin& m_pin;
  bool m_cache;

public:
  Channel(std::string const& name, Pin& pin) :
    AChannel(name), m_pin(pin), m_cache(pin.read())
  {}

  Channel(const Channel& orig) :
    AChannel(orig.m_name), m_pin(orig.m_pin), m_cache(orig.m_cache)
  {}

  virtual ~Channel() {}

  virtual void sync() {
    m_cache = m_pin.read();
  }

  virtual bool read() const {
    return m_cache;
  }

  virtual void write(bool value) {
    m_pin.write(value);
    m_cache = value;
  }
};

#endif	/* CHANNEL_H */

