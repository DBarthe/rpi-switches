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
public:
    Pin(AGpio& gpio);
    Pin(const Pin& orig);
    virtual ~Pin();

    bool read() const;
    void write(bool value);
    int getNum() const;
    
private:
    AGpio& m_gpio;
    int m_num;
};

#endif	/* PIN_H */

