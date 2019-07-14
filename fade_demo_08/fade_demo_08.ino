// Warning: This is a code example for the article "guideline for modular firmware".
//          It is code in a transition phase, do not use it as it is!

#include "Display.hpp"
#include "Buttons.hpp"
#include "Animation.hpp"


void onPlusPressed();
void onMinusPressed();


void setup() {
  Display::initialize();
  Buttons::initialize();
  Buttons::setCallback(Buttons::Plus, &onPlusPressed);
  Buttons::setCallback(Buttons::Minus, &onMinusPressed);
  Animation::initialize();
}

void loop() {
  Animation::progress();
  Buttons::poll();
  delay(50);
}


void onPlusPressed()
{  
  Animation::cycleMode(Animation::Next);
}


void onMinusPressed()
{
  Animation::cycleMode(Animation::Previous);
}
