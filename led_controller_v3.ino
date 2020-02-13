#include <FastLED.h>
#define NUM_LEDS 60
#define DATA_PIN 7


CRGB leds[NUM_LEDS];


char newData;


void setup() {
  Serial.begin(9600);
  Serial.flush();
  LEDS.addLeds<WS2812, DATA_PIN, RGB>(leds, NUM_LEDS);
  LEDS.setBrightness(150);
  colorSet(10, 0, 0); 
}

void loop() {
  if (Serial.available() > 0) {
    newData = Serial.read();
    Serial.flush();
    Serial.println(newData);
  }
  ledSwitch();
  delay(1);
}

void ledSwitch() {
  switch (newData) {
    case 'd':
      Serial.println("disabled");
      disabled();
      break;s
      
    case 'i':
      Serial.println("idle");
      idle(25);
      break;
    case 's':
      Serial.println("shoot");
      shoot();
      break;
    case 'c':
      Serial.println("climb");
      climb();
      break;
    case 'r':
      Serial.println("red");
      colorSet(0, 255, 0);
      break;
    case 'g':
      Serial.println("green");
      colorSet(255, 0, 0);
      break;
    case 'b':
      Serial.println("blue");
      colorSet(0, 0, 255);
      break;
    case 'p':
      Serial.println("cwred");
      cwSet(0, 255, 0);
      break;
    case 't':
      Serial.println("cwgreen");
      cwSet(255, 0, 0);
      break;
    case 'u':
      Serial.println("cwblue");
      cwSet(0, 0, 255);
      break;
    case 'y':
      Serial.println("cwyellow");
      cwSet(255, 255, 0);
      break;
    case 'o':
      turnOff();
      Serial.println("off");
      fadeall();
      FastLED.show();
      break;
    default:
      Serial.println("Error: Unexpected command");
  }
}

void fadeall() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i].nscale8(250);
  }
}

void idle(char speed) {
  static uint8_t hue = 0;
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CHSV(hue++, 255, 255);
    FastLED.show();
    fadeall();
    delay(speed);
  }
  for (int i = (NUM_LEDS) - 1; i >= 0; i--) {
    leds[i] = CHSV(hue++, 255, 255);
    FastLED.show();
    fadeall();
    delay(15);
  }
}

void turnOff() {
  static uint8_t hue = 0;
  for (int i = (NUM_LEDS) - 1; i >= 0; i--) {
    leds[i] = CHSV(0, 0, 0);
    FastLED.show();
    fadeall();
  }
}


void cwSet(char r, char g, char b) {
  static uint8_t hue = 0;
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(r, g, b);
    FastLED.show();
    fadeall();
    delay(5);
  }
  for (int i = (NUM_LEDS) - 1; i >= 0; i--) {
    leds[i] = CRGB(r, g, b);
    FastLED.show();
    fadeall();
    delay(5);
  }
}

void shoot() {
  static uint8_t hue = 0;
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(255, 0, 0);
    FastLED.show();
    fadeall();
    delay(4);
  }
}


void climb() {
  for (int j = 0; j < 1; j++) {
    for (int q = 0; q < 3; q++) {
      for (int i = 0; i < NUM_LEDS; i = i + 3) {
        int pos = i + q;
        leds[pos].setRGB(255, 0, 0);
      }
      FastLED.show();
      delay(100);
      for (int i = 0; i < NUM_LEDS; i = i + 3) {
        leds[i + q] = CRGB::Black;
      }
    }
  }
}

void colorSet(char r, char g, char b) {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i].setRGB(r, g, b);
    FastLED.show();
  }
}

void disabled() {

}
