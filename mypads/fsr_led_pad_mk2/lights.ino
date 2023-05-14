// BEGIN FASTLED SETUP
#include <FastLED.h>
#define NUM_STRIPS 4
#define NUM_LEDS 52
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB
#define BRIGHTNESS 150
#define VOLTS 5
#define MAX_AMPS 5000

//right down up left
CRGB leds[NUM_STRIPS][NUM_LEDS];
int currentColorSet = 0;
int TOTAL_FRAMES = 104;
int animationFrames[4] = {0, 0, 0, 0};
bool lightUpdateFlag = false;
unsigned long lastLightUpdate = 0;
uint32_t interval;

void lightInit() {
  // Add the LEDs
  FastLED.addLeds<LED_TYPE, 6, COLOR_ORDER>(leds[1], NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.addLeds<LED_TYPE, 5, COLOR_ORDER>(leds[3], NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.addLeds<LED_TYPE, 4, COLOR_ORDER>(leds[0], NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.addLeds<LED_TYPE, 3, COLOR_ORDER>(leds[2], NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setDither(0);
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.setMaxPowerInVoltsAndMilliamps(VOLTS, MAX_AMPS);
}

void endToEndIdle(int panelIndex, bool incrementFrame) {
  bool loopBack = animationFrames[panelIndex] < NUM_LEDS;
  int ledIndex = loopBack ? animationFrames[panelIndex] : animationFrames[panelIndex] - NUM_LEDS;

  CRGB color;
  switch(panelIndex) {
    case 0:
    case 3:
      color = loopBack ? colorSets[currentColorSet][1] : colorSets[currentColorSet][0];
      break;
    case 1:
    case 2:
      color = loopBack ? colorSets[currentColorSet][3] : colorSets[currentColorSet][2];
      break;
  }

  leds[panelIndex][ledIndex] = color;

  if(incrementFrame) {
    animationFrames[panelIndex]++;
    if(animationFrames[panelIndex] >= TOTAL_FRAMES) { animationFrames[panelIndex] = 0; }
  }
}

void clearPanelLEDs(int k) {
  int offset = 7;
  int offset2 = (NUM_LEDS/2) + offset;

  if(k > 3) {
    k = k - 4;
    for(int i = offset; i < offset2; i++) { leds[k][i] = CRGB::Black; }
  } else {
    for(int i = 0; i < offset; i++) { leds[k][i] = CRGB::Black; }
    for(int i = offset2; i < NUM_LEDS; i++) { leds[k][i] = CRGB::Black; }
  }
  FastLED.show();
}

void activePanelLEDs(int k) {
  int offset = 7;
  int offset2 = (NUM_LEDS/2) + offset;

  if(k > 3) {
    k = k - 4;
    for(int i = offset; i < offset2; i++) { leds[k][i] = CRGB::White; }
  } else {
    for(int i = 0; i < offset; i++) { leds[k][i] = CRGB::White; }
    for(int i = offset2; i < NUM_LEDS; i++) { leds[k][i] = CRGB::White; }
  }
  FastLED.show();
}

void checkLightTiming() {
  if (millis() - lastLightUpdate >= 20) {
    lastLightUpdate = millis();
    lightUpdateFlag = true;
  } else {
    lightUpdateFlag = false;
  }
}

void showLights() {
  FastLED.show();
}