#include "Display.hpp"

// Warning: This is a code example for the article "guideline for modular firmware".
//          It is code in a transition phase, do not use it as it is!

namespace Display {


const uint8_t cMaximumLevel        = 0x20;
const uint8_t cLedCount            = 3;
const uint8_t cOrangeMask          = 0b00001000u;
const uint8_t cGreenMask           = 0b00010000u;
const uint8_t cRedMask             = 0b00100000u;
const uint8_t cAllLedsMask         = cOrangeMask|cGreenMask|cRedMask;
const uint8_t cLedMask[cLedCount]  = {cOrangeMask, cGreenMask, cRedMask};

volatile uint8_t gFadeCounter      = 0;
volatile uint8_t gLevel[cLedCount];


void initialize()
{
  // Initialize the time and enable the interrupt.
  TCCR2A = 0;
  TCCR2B = 1;
  OCR2A = 0;
  OCR2B = 0;
  TIMSK2 = _BV(TOIE2);
  // Set all LED pins in output mode.
  DDRB |= cAllLedsMask;
  PORTB &= ~cAllLedsMask;
  // Set all levels to zero.
  for (uint8_t i = 0; i < cLedCount; ++i) {
    gLevel[i] = 0;
  }
}


uint8_t getMaximumLevel()
{
  return cMaximumLevel;  
}


uint8_t getLevel(Color color)
{
  return getLevel(static_cast<uint8_t>(color));
}


uint8_t getLevel(uint8_t index)
{
  return gLevel[index];
}


void setLevel(Color color, uint8_t level)
{
  setLevel(static_cast<uint8_t>(color), level);
}


void setLevel(uint8_t index, uint8_t level)
{
  gLevel[index] = level;  
}


inline void timerInterrupt()
{
  ++gFadeCounter;
  gFadeCounter &= 0x1f;
  uint8_t mask = 0;
  for (uint8_t i = 0; i < cLedCount; ++i) {
    if (gFadeCounter < gLevel[i]) {
      mask |= cLedMask[i];
    }
  }
  PORTB = ((PORTB & ~cAllLedsMask) | mask);  
}

  
}


ISR(TIMER2_OVF_vect)
{
  Display::timerInterrupt();
}
