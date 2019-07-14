#pragma once

// Warning: This is a code example for the article "guideline for modular firmware".
//          It is code in a transition phase, do not use it as it is!

#include <Arduino.h>

class AnimationMode
{
public:
  virtual void initialize() = 0;
  virtual void progress() = 0;
};


class AnimationModeFade : public AnimationMode
{
public: // Implement AnimationMode
  void initialize() override;
  void progress() override;
private:
  bool _orangeDirection;
  bool _greenDirection;
  bool _redDirection;
};


class AnimationModeRoll : public AnimationMode
{
public:
  enum Direction { Left, Right };
public:
  AnimationModeRoll(Direction direction);
public: // Implement AnimationMode
  void initialize() override;
  void progress() override;
private:
  void updateLeds();
private:
  constexpr static uint8_t _speed = 8;
  const Direction _direction;
  uint8_t _counter;
  uint8_t _index;
};

class AnimationModeBlink : public AnimationMode
{
public: // Implement AnimationMode
  void initialize() override;
  void progress() override;  
private:
  constexpr static uint8_t _speed = 10;
  uint8_t _counter;
};
