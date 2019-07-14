#include "AnimationMode.hpp"

// Warning: This is a code example for the article "guideline for modular firmware".
//          It is code in a transition phase, do not use it as it is!


#include "Display.hpp"


void AnimationModeFade::initialize()
{
  for (uint8_t i = 0; i < 3; ++i) {
    _direction[i] = true;
    Display::setLevel(i, i*8);    
  }
}


void AnimationModeFade::progress()
{
  for (uint8_t i = 0; i < 3; ++i) {
    if (_direction[i]) {
      auto level = Display::getLevel(i);
      ++level;
      Display::setLevel(i, level);
      if (level == Display::getMaximumLevel()) {
        _direction[i] = false;
      }
    } else {
      auto level = Display::getLevel(i);
      --level;
      Display::setLevel(i, level);
      if (level == 0) {
        _direction[i] = true;      
      }
    }
  }
}


AnimationModeRoll::AnimationModeRoll(Direction direction)
  : _direction(direction)
{
}


void AnimationModeRoll::initialize()
{
  _index = 0;
  _counter = 0;
}


void AnimationModeRoll::progress()
{
  ++_counter;
  if (_counter >= _speed) {
    _counter = 0;
    if (_direction == Left) {
      _index += 1;
    } else {
      _index -= 1;
    }
    _index &= 0x3;
    updateLeds();
  }
}


void AnimationModeRoll::updateLeds()
{
    for (uint8_t i = 0; i < 3; ++i) {
      Display::setLevel(i, ((_index + i) & 0x3) * 8);
    }
}


void AnimationModeBlink::initialize()
{
  _counter = 0;
  for (uint8_t i = 0; i < 3; ++i) {
    Display::setLevel(i, 0);
  }
}


void AnimationModeBlink::progress()
{
  ++_counter;
  if (_counter >= _speed) {
    _counter = 0;
    auto level = Display::getLevel(Display::Color::Orange);
    if (level != 0) {
      level = 0;
    } else {
      level = Display::getMaximumLevel();
    }
    for (uint8_t i = 0; i < 3; ++i) {
      Display::setLevel(i, level);
    }
  }
}
