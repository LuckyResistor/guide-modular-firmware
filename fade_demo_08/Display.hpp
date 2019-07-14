#pragma once

// Warning: This is a code example for the article "guideline for modular firmware".
//          It is code in a transition phase, do not use it as it is!

#include <Arduino.h>

/// The display module to control the attached LEDs
///
namespace Display {


/// The color of the LED
///
enum class Color : uint8_t {
  Orange = 0,
  Green = 1,
  Red = 2
};

/// Initialize the display module.
///
void initialize();

/// Get the maximum level.
///
/// @return The maximum level value.
///
uint8_t getMaximumLevel();

/// Get the level of the givem LED.
///
/// @param color The color of the LED to retrieve.
///
uint8_t getLevel(Color color);

/// Get the level of the givem LED.
///
/// @param index The index of the LED to retrieve (0-2).
///
uint8_t getLevel(uint8_t index);

/// Set the level of the given LED.
///
/// @param color The color of the LED to change.
/// @param level The level for the LED.
///
void setLevel(Color color, uint8_t level);

/// Set the level of the given LED.
///
/// @param index The index of the LED to change (0-2).
/// @param level The level for the LED.
///
void setLevel(uint8_t index, uint8_t level);


}
