#include <FastLED.h>
#define NUM_LEDS 40
#define DATA_PIN 3


CRGB leds[NUM_LEDS];



// white is vertical
// red is horizotal
char newData = 0;
char dropDriveState = 0;
void setup() {
  Serial.begin(115200);   // Start Serial @ 115200 baud
  Serial.flush();       // Clear  buffer

  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
}

void loop() {
  if (Serial.available() > 0) {        // Check buffer
    newData = Serial.read();            // Save string received
    Serial.flush();                    // Clear buffer

    switch (newData) {

      case 'a':                        // Idle vertical
        idleV(20);
        Serial.println("IDLE-VERT-TESTING");
        FastLED.show();
        break;


      case 'b':  //Idle horizontal
        idleH(20);
        Serial.println("IDLE-HORIZ-TESTING");
        FastLED.show();
        break;

      case 'c':                        // Intake
        Serial.println("INTAKE-TESTING");
        if (dropDriveState == 1) {
           RunningLights(0xff,0xff,0xff, 50);  // white
          FastLED.show();
        } else {
           RunningLights(0xff,0,0, 50);        // red
          FastLED.show();
        }
        break;



      case 'd':                        // Deploy
        Serial.println("DEPLOY-TESTING");
        if (dropDriveState == 1) {
          //deployDD();
          FastLED.show();
        } else {
          deploy();          FastLED.show();
        }
        break;



      case 'e':                        // Drop Drive Down
        dropDrive();
        Serial.println("DRIVE-TESTING");
        dropDriveState = 1; // allows the others to use the horizontal strip for drop drive while drop drive is active
        FastLED.show();

        break;



      case 'f':                        // Drop Drive Up
        Serial.println("DRIVE-UP-TESTING");
        dropDriveState = 0; // gives full access to the horizontal strip while drop drive is inactive
        prevoiusState();
        break;



      case 'g':                        // Elevator Up
        elev();
        Serial.println("ELEV-TESTING");
        FastLED.show();

        break;


      case 'h':                        // Winch
        winch();
        Serial.println("WINCH-TESTING");
        FastLED.show();
        break;


      case 'i':                        // Off
        Serial.println("OFF-TESTING");


        break;


      default:
        Serial.println("Error: Unexpected command");
    }
  }


}

void idleH(int SpeedDelay) {
  byte *c;
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< 10; i++) {
      c=Wheel(((i * 256 / NUM_LEDS) + j) & 255);
      setPixel(i, *c, *(c+1), *(c+2));
    }
    showStrip();
    delay(SpeedDelay);
  }
}



void idleH(int SpeedDelay) {
  byte *c;
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=11; i< 28; i++) {
      c=Wheel(((i * 256 / NUM_LEDS) + j) & 255);
      setPixel(i, *c, *(c+1), *(c+2));
    }
    showStrip();
    delay(SpeedDelay);
  }
}





byte * Wheel(byte WheelPos) {
  static byte c[3];
  
  if(WheelPos < 85) {
   c[0]=WheelPos * 3;
   c[1]=255 - WheelPos * 3;
   c[2]=0;
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   c[0]=255 - WheelPos * 3;
   c[1]=0;
   c[2]=WheelPos * 3;
  } else {
   WheelPos -= 170;
   c[0]=0;
   c[1]=WheelPos * 3;
   c[2]=255 - WheelPos * 3;
  }

  return c;
}


void RunningLights(byte red, byte green, byte blue, int WaveDelay) {
  int Position=0;
  
  for(int i=0; i<NUM_LEDS*2; i++)
  {
      Position++; // = 0; //Position + Rate;
      for(int i=0; i<10; i++) {
        // sine wave, 3 offset waves make a rainbow!
        //float level = sin(i+Position) * 127 + 128;
        //setPixel(i,level,0,0);
        //float level = sin(i+Position) * 127 + 128;
        setPixel(i,((sin(i+Position) * 127 + 128)/255)*red,
                   ((sin(i+Position) * 127 + 128)/255)*green,
                   ((sin(i+Position) * 127 + 128)/255)*blue);
      }
      
      showStrip();
      delay(WaveDelay);
  }
}
