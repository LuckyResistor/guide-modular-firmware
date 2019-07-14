#include "AnimationMode.hpp"

// Warning: This is a code example for the article "guideline for modular firmware".
//          It is code in a transition phase, do not use it as it is!


#include "Display.hpp"


void AnimationModeFade::initialize()
{
  _orangeDirection = true;
  _greenDirection = true;
  _redDirection = true;
  Display::setLevel(Display::Color::Orange, 0x0c);
  Display::setLevel(Display::Color::Green, 0x12);
  Display::setLevel(Display::Color::Red, 0x18);
}


void AnimationModeFade::progress()
{
  if (_orangeDirection) {
    auto level = Display::getLevel(Display::Color::Orange);
    ++level;
    Display::setLevel(Display::Color::Orange, level);
    if (level == Display::getMaximumLevel()) {
      _orangeDirection = false;
    }
  } else {
    auto level = Display::getLevel(Display::Color::Orange);
    --level;
    Display::setLevel(Display::Color::Orange, level);
    if (level == 0) {
      _orangeDirection = true;      
    }
  }
  if (_greenDirection) {
    auto level = Display::getLevel(Display::Color::Green);
    ++level;
    Display::setLevel(Display::Color::Green, level);
    if (level == Display::getMaximumLevel()) {
      _greenDirection = false;
    }
  } else {
    auto level = Display::getLevel(Display::Color::Green);
    --level;
    Display::setLevel(Display::Color::Green, level);
    if (level == 0) {
      _greenDirection = true;      
    }
  }
  if (!_redDirection) {
    auto level = Display::getLevel(Display::Color::Red);
    --level;
    Display::setLevel(Display::Color::Red, level);
    if (level == 0) {
      _redDirection = true;      
    }
  } else {
    auto level = Display::getLevel(Display::Color::Red);
    ++level;
    Display::setLevel(Display::Color::Red, level);
    if (level == Display::getMaximumLevel()) {
      _redDirection = false;
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
    Display::setLevel(Display::Color::Green, ((_index + 1) & 0x3) * 8);
    Display::setLevel(Display::Color::Orange, (_index & 0x3) * 8);
    Display::setLevel(Display::Color::Red, ((_index + 2) & 0x3) * 8);
  }
}


void AnimationModeRoll::updateLeds()
{
  Display::setLevel(Display::Color::Orange, (_index & 0x3) * 8);
  Display::setLevel(Display::Color::Green, ((_index + 1) & 0x3) * 8);
  Display::setLevel(Display::Color::Red, ((_index + 2) & 0x3) * 8);  
}


void AnimationModeBlink::initialize()
{
  _counter = 0;
  Display::setLevel(Display::Color::Orange, 0);
  Display::setLevel(Display::Color::Green, 0);
  Display::setLevel(Display::Color::Red, 0);  
}


void AnimationModeBlink::progress()
{
  ++_counter;
  if (_counter >= _speed) {
    _counter = 0;
    auto orangeLevel = Display::getLevel(Display::Color::Orange);
    if (orangeLevel != 0) {
      Display::setLevel(Display::Color::Orange, 0);
      Display::setLevel(Display::Color::Green, 0);
      Display::setLevel(Display::Color::Red, 0);
    } else {
      Display::setLevel(Display::Color::Orange, Display::getMaximumLevel());
      Display::setLevel(Display::Color::Green, Display::getMaximumLevel());
      Display::setLevel(Display::Color::Red, Display::getMaximumLevel());
    }
  }
}
