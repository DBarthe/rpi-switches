/* 
 * File:   AChannel.h
 * Author: barth
 *
 * Created on 30 novembre 2014, 20:37
 */

#ifndef ACHANNEL_H
#define	ACHANNEL_H

#include <string>

class AChannel {

protected:
    std::string m_name;

public:
    AChannel(std::string const& name) : m_name(name) {}
    AChannel(const AChannel& orig) : m_name(orig.m_name) {}
    virtual ~AChannel() {}
    
    std::string const& getName() const {
      return m_name;
    }
    
    virtual void sync() = 0;
    virtual bool read() const = 0;
    virtual void write(bool value) = 0;
};

#endif	/* ACHANNEL_H */

