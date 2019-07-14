#include "Buttons.hpp"

// Warning: This is a code example for the article "guideline for modular firmware".
//          It is code in a transition phase, do not use it as it is!

namespace Buttons {


bool gLastButtonA = true;
bool gLastButtonB = true;
Function gPlusCallback = nullptr;
Function gMinusCallback = nullptr;


void initialize()
{
  DDRB &= ~0b00000110;
  PORTB |= 0b00000110; 
}


void setCallback(Button button, Function fn)
{
  switch (button) {
  case Plus: gPlusCallback = fn; break;
  case Minus: gMinusCallback = fn; break;
  default: break;
  }
}


void poll()
{
  Button pressedButton = NoButton;
  const uint8_t pinInput = PINB;
  const bool buttonPressA = ((pinInput & 0b00000100) != 0);
  if (buttonPressA != gLastButtonA) {
    if (!buttonPressA) {
      pressedButton = Plus;
    }
    gLastButtonA = buttonPressA;
  }
  bool buttonPressB = (pinInput & 0b00000010);
  if (buttonPressB != gLastButtonB) {
    if (!buttonPressB) {
      pressedButton = Minus;
    }
    gLastButtonB = buttonPressB;
  }
  switch (pressedButton) {
  case Plus: gPlusCallback(); break;
  case Minus: gMinusCallback(); break;
  default: break;
  }
}

  
}
