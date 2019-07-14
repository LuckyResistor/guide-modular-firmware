#include "Animation.hpp"

// Warning: This is a code example for the article "guideline for modular firmware".
//          It is code in a transition phase, do not use it as it is!

#include "Display.hpp"
#include "AnimationMode.hpp"


namespace Animation {


const uint8_t cModeCount = 4;

AnimationMode* const gAnimation[] = {
  new AnimationModeFade(),
  new AnimationModeRoll(AnimationModeRoll::Left),
  new AnimationModeRoll(AnimationModeRoll::Right),
  new AnimationModeBlink(),
};
Mode gCurrentMode = Mode::Fade;

const uint8_t cShiftSpeed = 8;
const uint8_t cBlinkSpeed = 10;
uint8_t gLedIndex = 0;
uint8_t gLedCounter = 0;
bool gLedDirection = false;
bool gOrangeDirection = true;
bool gGreenDirection = true;
bool gRedDirection = true;


void initialize()
{
  gAnimation[static_cast<uint8_t>(gCurrentMode)]->initialize();
}


void setMode(Mode mode)
{
  if (gCurrentMode != mode) {
    gCurrentMode = mode;
    gAnimation[static_cast<uint8_t>(gCurrentMode)]->initialize();
  }
}


void cycleMode(CycleDirection cycleDirection)
{
  uint8_t mode = static_cast<uint8_t>(gCurrentMode);
  if (cycleDirection == Next) {
    ++mode;
  } else {
    --mode;
  }
  mode &= 0x3;
  setMode(static_cast<Mode>(mode));
}


void progress()
{
  gAnimation[static_cast<uint8_t>(gCurrentMode)]->progress();
}

  
}
