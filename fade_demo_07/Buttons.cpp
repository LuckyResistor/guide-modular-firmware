#include "Buttons.hpp"

// Warning: This is a code example for the article "guideline for modular firmware".
//          It is code in a transition phase, do not use it as it is!

namespace Buttons {


const uint8_t cButtonCount      = 2;
const uint8_t cPlusButtonMask   = 0b00000100u;
const uint8_t cMinusButtonMask  = 0b00000010u;
const uint8_t cAllButtonMasks   = cPlusButtonMask|cMinusButtonMask;
const uint8_t cButtonMask[]     = {cPlusButtonMask, cMinusButtonMask};
const Button cButton[]          = {Plus, Minus};

bool gLastState[cButtonCount];
Function gCallback[cButtonCount];


void initialize()
{
  // Set all button pins to input with a pull-up
  DDRB &= ~cAllButtonMasks;
  PORTB |= cAllButtonMasks;
  // Set the last state to true.
  memset(gLastState, static_cast<uint8_t>(true), sizeof gLastState);
  // Set all callbacks to `nullptr`
  memset(gCallback, 0, sizeof gCallback);
}


void setCallback(Button button, Function fn)
{
  gCallback[static_cast<uint8_t>(button)] = fn;
}


void poll()
{
  uint8_t pressedButtonIndex = cButtonCount;
  const uint8_t pinInput = PINB;
  for (uint8_t i = 0; i < cButtonCount; ++i) {
    const bool buttonPressed = ((pinInput & cButtonMask[i]) != 0);
    if (buttonPressed != gLastState[i]) {
      gLastState[i] = buttonPressed;
      if (!buttonPressed) {
        pressedButtonIndex = i;
      }
    }
  }
  if (pressedButtonIndex < cButtonCount) {
    if (gCallback[pressedButtonIndex] != nullptr) {
      gCallback[pressedButtonIndex]();
    }
  }
}

  
}
