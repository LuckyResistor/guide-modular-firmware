// Warning: This is a code example for the article "guideline for modular firmware".
//          It is code in a transition phase, do not use it as it is!

#include "Display.hpp"
#include "Buttons.hpp"

const uint8_t cModeCount = 4;
const uint8_t cShiftSpeed = 8;
const uint8_t cBlinkSpeed = 10;
uint8_t gLedMode = 0;
uint8_t gLedIndex = 0;
uint8_t gLedCounter = 0;
bool gLedDirection = false;
bool gOrangeDirection = true;
bool gGreenDirection = true;
bool gRedDirection = true;

void onPlusPressed();
void onMinusPressed();

void setup() {
  Display::initialize();
  Buttons::initialize();
  Buttons::setCallback(Buttons::Plus, &onPlusPressed);
  Buttons::setCallback(Buttons::Minus, &onMinusPressed);
}

void loop() {
  if (gLedMode == 0) {
    if (gOrangeDirection) {
      auto level = Display::getLevel(Display::Color::Orange);
      ++level;
      Display::setLevel(Display::Color::Orange, level);
      if (level == Display::getMaximumLevel()) {
        gOrangeDirection = false;
      }
    } else {
      auto level = Display::getLevel(Display::Color::Orange);
      --level;
      Display::setLevel(Display::Color::Orange, level);
      if (level == 0) {
        gOrangeDirection = true;      
      }
    }
    if (gGreenDirection) {
      auto level = Display::getLevel(Display::Color::Green);
      ++level;
      Display::setLevel(Display::Color::Green, level);
      if (level == Display::getMaximumLevel()) {
        gGreenDirection = false;
      }
    } else {
      auto level = Display::getLevel(Display::Color::Green);
      --level;
      Display::setLevel(Display::Color::Green, level);
      if (level == 0) {
        gGreenDirection = true;      
      }
    }
    if (!gRedDirection) {
      auto level = Display::getLevel(Display::Color::Red);
      --level;
      Display::setLevel(Display::Color::Red, level);
      if (level == 0) {
        gRedDirection = true;      
      }
    } else {
      auto level = Display::getLevel(Display::Color::Red);
      ++level;
      Display::setLevel(Display::Color::Red, level);
      if (level == Display::getMaximumLevel()) {
        gRedDirection = !gRedDirection;
      }
    }  
  } else if (gLedMode == 1) {
    ++gLedCounter;
    if (gLedCounter >= cShiftSpeed) {
      gLedCounter = 0;
      gLedIndex = ((gLedIndex + 1) & 0x3);
      Display::setLevel(Display::Color::Green, ((gLedIndex + 1) & 0x3) * 8);
      Display::setLevel(Display::Color::Orange, (gLedIndex & 0x3) * 8);
      Display::setLevel(Display::Color::Red, ((gLedIndex + 2) & 0x3) * 8);
    }
  } else if (gLedMode == 2) {
    ++gLedCounter;
    if (gLedCounter >= cShiftSpeed) {
      --gLedIndex;
      gLedIndex &= 0x3;
      gLedCounter = 0;
      Display::setLevel(Display::Color::Orange, (gLedIndex & 0x3) * 8);
      Display::setLevel(Display::Color::Green, ((gLedIndex + 1) & 0x3) * 8);
      Display::setLevel(Display::Color::Red, ((gLedIndex + 2) & 0x3) * 8);
    }    
  } else if (gLedMode == 3) {
    ++gLedCounter;
    if (gLedCounter >= cBlinkSpeed) {
      gLedCounter = 0;
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
  Buttons::poll();
  delay(50);
}


void initializeMode()
{
  if (gLedMode == 0) {
    Display::setLevel(Display::Color::Orange, 0x0c);
    Display::setLevel(Display::Color::Green, 0x12);
    Display::setLevel(Display::Color::Red, 0x18);
  } else if (gLedMode == 1) {
    gLedIndex = 0;
    gLedDirection = true;
    Display::setLevel(Display::Color::Orange, (gLedIndex & 0x3) * 8);
    Display::setLevel(Display::Color::Green, ((gLedIndex + 1) & 0x3) * 8);
    Display::setLevel(Display::Color::Red, ((gLedIndex + 2) & 0x3) * 8);
    gLedCounter = 0;
  } else if (gLedMode == 2) {
    gLedIndex = 0;
    gLedDirection = false;
    Display::setLevel(Display::Color::Orange, (gLedIndex & 0x3) * 8);
    Display::setLevel(Display::Color::Green, ((gLedIndex + 1) & 0x3) * 8);
    Display::setLevel(Display::Color::Red, ((gLedIndex + 2) & 0x3) * 8);
    gLedCounter = 0;
  }  
}


void onPlusPressed()
{
  ++gLedMode;
  if (gLedMode >= cModeCount) {
    gLedMode = 0;
  }
  initializeMode(); 
}


void onMinusPressed()
{
  if (gLedMode == 0) {
    gLedMode = (cModeCount-1);
  } else {
    --gLedMode;
  }
  initializeMode(); 
}
