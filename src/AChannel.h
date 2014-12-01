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
public:
    AChannel();
    AChannel(const AChannel& orig);
    virtual ~AChannel();
    
    std::string const& getName() const;
    
    virtual void sync() = 0;
    virtual bool read() const = 0;
    virtual bool write(bool value) = 0;
    
private:
    std::string m_name;
    
};

#endif	/* ACHANNEL_H */

