#pragma once

// Warning: This is a code example for the article "guideline for modular firmware".
//          It is code in a transition phase, do not use it as it is!

#include <Arduino.h>

/// The module to animate the LEDs
///
namespace Animation {


/// The animation mode.
///
enum class Mode : uint8_t {
  Fade = 0,
  RollRight = 1,
  RollLeft = 2,
  Blink = 3
};


/// The Cycle Direction.
///
enum CycleDirection : uint8_t {
  Next,
  Previous
};


/// Initialize the animation module.
///
void initialize();

/// Set the current animation mode.
///
void setMode(Mode mode);

/// Cycle the current mode.
///
void cycleMode(CycleDirection cycleDirection);

/// Get the current animation mode.
///
Mode getMode();

/// Progress the current animation.
///
void progress();

  
}
