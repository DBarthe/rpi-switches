/* 
 * File:   SimulatedGpio.h
 * Author: barth
 *
 * Created on 30 novembre 2014, 23:09
 */

#ifndef SIMULATEDGPIO_H
#define	SIMULATEDGPIO_H

#include <array>
#include <cassert>
#include <iostream>
#include <algorithm>

#include "IGpio.h"

class SimulatedGpio : public IGpio { 

    static const int MAX_PIN_NUM = 26;
    static void assert_range(int pin_num) {
      assert(pin_num >= 0 && pin_num <= MAX_PIN_NUM);
    }

    enum PinValue { Uninit, High, Low };
    std::array<PinValue, MAX_PIN_NUM + 1> m_pin_board;

public:
    SimulatedGpio() :
      IGpio(),
      m_pin_board({Uninit})
    {}

    SimulatedGpio(const SimulatedGpio& orig) :
      IGpio(),
      m_pin_board()
    {
      std::copy(orig.m_pin_board.begin(), orig.m_pin_board.end(), m_pin_board.begin());
    }

    virtual ~SimulatedGpio() {}
    
    virtual bool read(int pin_num) const {
      assert_range(pin_num);
      PinValue value = m_pin_board[pin_num];
      assert(value != Uninit);
      return (value == High) ? true : false;
    }

    virtual void write(int pin_num, bool value) {
      assert_range(pin_num);
      assert(m_pin_board[pin_num] != Uninit);
      m_pin_board[pin_num] = (value ? High : Low);
    }

    virtual void init(int pin_num) {
      assert_range(pin_num);

      switch (m_pin_board[pin_num]) {
        case Uninit:
          m_pin_board[pin_num] = Low;
          break;
        default:
          std::cerr << "SimulatedGpio: warning: re-initialization of pin "
                    << pin_num << std::endl;
      }
    }

    virtual void reset() {
      for (auto& v : m_pin_board) {
        v = Uninit;
      }
    }
    
};

#endif	/* SIMULATEDGPIO_H */
