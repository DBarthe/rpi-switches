/* 
 * File:   Pin.cpp
 * Author: barth
 * 
 * Created on 30 novembre 2014, 20:29
 */

#include "Pin.h"

Pin::Pin(AGpio& gpio) : m_gpio(gpio) {
}

Pin::Pin(const Pin& orig) : m_gpio(orig.m_gpio) {
}

Pin::~Pin() {
}

