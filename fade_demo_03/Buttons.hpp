#pragma once

#include <Arduino.h>

// Warning: This is a code example for the article "guideline for modular firmware".
//          It is code in a transition phase, do not use it as it is!

/// A module to handle button presses.
///
namespace Buttons {

/// The callback function.
///
typedef void (*Function)();

/// The button.
///
enum Button : uint8_t {
  NoButton = 0,
  Plus = 1,
  Minus = 2
};


/// Initialize the buttons module.
///
void initialize();

/// Set a callback if the given button is pressed.
///
void setCallback(Button button, Function fn);

/// Poll the button states.
///
void poll();

 
}
