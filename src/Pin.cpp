/* 
 * File:   Pin.cpp
 * Author: barth
 * 
 * Created on 30 novembre 2014, 20:29
 */

#include "Pin.h"
#include "GpioWrapper.h"
 
AGpio& Pin::s_gpio = GpioWrapper::unwrap();