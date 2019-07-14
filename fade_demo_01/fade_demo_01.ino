// Warning: This is a bad code example for the article "guideline for modular firmware".
//          Please never write code like this!

const uint8_t cMaxLevel = 0x20;
const uint8_t cModeCount = 4;
const uint8_t cShiftSpeed = 8;
const uint8_t cBlinkSpeed = 10;
volatile uint8_t gFadeCounter = 0;
volatile uint8_t gOrangeLevel = 0x0c;
volatile uint8_t gGreenLevel = 0x12;
volatile uint8_t gRedLevel = 0x18;
uint8_t gLedMode = 0;
uint8_t gLedIndex = 0;
uint8_t gLedCounter = 0;
bool gLedDirection = false;
bool gLastButtonA = true;
bool gLastButtonB = true;
bool gOrangeDirection = true;
bool gGreenDirection = true;
bool gRedDirection = true;

void setup() {
  // Initialize Timer
  TCCR2A = 0;
  TCCR2B = 1;
  OCR2A = 0;
  OCR2B = 0;
  TIMSK2 = _BV(TOIE2);
  // Ports
  DDRB |= 0b00111000;
  DDRB &= ~0b00000110;
  PORTB &= ~0b00111000;
  PORTB |= 0b00000110;
}

void loop() {
  if (gLedMode == 0) {
    if (gOrangeDirection) {
      ++gOrangeLevel;
      if (gOrangeLevel == cMaxLevel) {
        gOrangeDirection = false;
      }
    } else {
      --gOrangeLevel;
      if (gOrangeLevel == 0) {
        gOrangeDirection = true;      
      }
    }
    if (gGreenDirection) {
      gGreenLevel += 1;
      if (gGreenLevel == cMaxLevel) {
        gGreenDirection = false;
      }
    } else {
      --gGreenLevel;
      if (gGreenLevel == 0) {
        gGreenDirection = true;      
      }
    }
    if (!gRedDirection) {
      --gRedLevel;
      if (gRedLevel == 0) {
        gRedDirection = true;      
      }
    } else {
      ++gRedLevel;
      if (gRedLevel == 0x20) {
        gRedDirection = !gRedDirection;
      }
    }  
  } else if (gLedMode == 1) {
    ++gLedCounter;
    if (gLedCounter >= cShiftSpeed) {
      gLedCounter = 0;
      gLedIndex = ((gLedIndex + 1) & 0x3);
      gGreenLevel = ((gLedIndex + 1) & 0x3) * 8;
      gOrangeLevel = (gLedIndex & 0x3) * 8;
      gRedLevel = ((gLedIndex + 2) & 0x3) * 8;
    }
  } else if (gLedMode == 2) {
    ++gLedCounter;
    if (gLedCounter >= cShiftSpeed) {
      --gLedIndex;
      gLedIndex &= 0x3;
      gLedCounter = 0;
      gOrangeLevel = (gLedIndex & 0x3) * 8;
      gGreenLevel = ((gLedIndex + 1) & 0x3) * 8;
      gRedLevel = ((gLedIndex + 2) & 0x3) * 8;
    }    
  } else if (gLedMode == 3) {
    ++gLedCounter;
    if (gLedCounter >= cBlinkSpeed) {
      gLedCounter = 0;
      if (gOrangeLevel != 0) {
        gOrangeLevel = 0;
        gGreenLevel = 0;
        gRedLevel = 0;
      } else {
        gOrangeLevel = cMaxLevel;
        gGreenLevel = cMaxLevel;
        gRedLevel = cMaxLevel;        
      }
    }
  }
  bool modeNeedsInitialization = false;
  const uint8_t pinInput = PINB;
  const bool buttonPressA = ((pinInput & 0b00000100) != 0);
  if (buttonPressA != gLastButtonA) {
    if (!buttonPressA) {
      ++gLedMode;
      if (gLedMode >= cModeCount) {
        gLedMode = 0;
      }
      modeNeedsInitialization = true;
    }
    gLastButtonA = buttonPressA;
  }
  bool buttonPressB = (pinInput & 0b00000010);
  if (buttonPressB != gLastButtonB) {
    if (!buttonPressB) {
      if (gLedMode == 0) {
        gLedMode = (cModeCount-1);
      } else {
        --gLedMode;
      }
      modeNeedsInitialization = true;
    }
    gLastButtonB = buttonPressB;
  }
  if (modeNeedsInitialization) {
    if (gLedMode == 0) {
      gOrangeLevel = 0x0c;
      gGreenLevel = 0x12;
      gRedLevel = 0x18;
    } else if (gLedMode == 1) {
      gLedIndex = 0;
      gLedDirection = true;
      gOrangeLevel = (gLedIndex & 0x3) * 8;
      gGreenLevel = ((gLedIndex + 1) & 0x3) * 8;
      gRedLevel = ((gLedIndex + 2) & 0x3) * 8;
      gLedCounter = 0;
    } else if (gLedMode == 2) {
      gLedIndex = 0;
      gLedDirection = false;
      gOrangeLevel = (gLedIndex & 0x3) * 8;
      gGreenLevel = ((gLedIndex + 1) & 0x3) * 8;
      gRedLevel = ((gLedIndex + 2) & 0x3) * 8;
      gLedCounter = 0;
    }
  }
  delay(50);
}

ISR(TIMER2_OVF_vect)
{
  ++gFadeCounter;
  gFadeCounter &= 0x1f;
  uint8_t mask = 0;
  if (gFadeCounter < gOrangeLevel) {
    mask |= 0b100000;
  }
  if (gFadeCounter < gGreenLevel) {
    mask |= 0b010000;
  }
  if (gFadeCounter < gRedLevel) {
    mask |= 0b001000;
  }
  PORTB = ((PORTB & ~0b111000) | mask);
}
