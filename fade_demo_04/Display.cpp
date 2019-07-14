#include "Display.hpp"

// Warning: This is a code example for the article "guideline for modular firmware".
//          It is code in a transition phase, do not use it as it is!

namespace Display {


const uint8_t cMaxLevel = 0x20;

volatile uint8_t gFadeCounter = 0;
volatile uint8_t gOrangeLevel = 0x0c;
volatile uint8_t gGreenLevel = 0x12;
volatile uint8_t gRedLevel = 0x18;


void initialize()
{
  // Initialize Timer
  TCCR2A = 0;
  TCCR2B = 1;
  OCR2A = 0;
  OCR2B = 0;
  TIMSK2 = _BV(TOIE2);
  // Ports
  DDRB |= 0b00111000;
  PORTB &= ~0b00111000;
}


uint8_t getMaximumLevel()
{
  return cMaxLevel;  
}


uint8_t getLevel(Color color)
{
  switch (color) {
  case Color::Orange: return gOrangeLevel;
  case Color::Green: return gGreenLevel;
  case Color::Red: return gRedLevel;
  }
  return 0;
}


void setLevel(Color color, uint8_t level)
{
  switch (color) {
  case Color::Orange: gOrangeLevel = level; break;
  case Color::Green: gGreenLevel = level; break;
  case Color::Red: gRedLevel = level; break;
  }
}


inline void timerInterrupt()
{
  ++gFadeCounter;
  gFadeCounter &= 0x1f;
  uint8_t mask = 0;
  if (gFadeCounter < gOrangeLevel) {
    mask |= 0b100000;
  }
  if (gFadeCounter < gGreenLevel) {
    mask |= 0b010000;
  }
  if (gFadeCounter < gRedLevel) {
    mask |= 0b001000;
  }
  PORTB = ((PORTB & ~0b111000) | mask);  
}

  
}


ISR(TIMER2_OVF_vect)
{
  Display::timerInterrupt();
}
