#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN 6

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(2, PIN, NEO_GRB + NEO_KHZ800);


// white is vertical
// red is horizotal
char newData = 0;
char dropDriveState = 0;
void setup() {
  Serial.begin(115200);   // Start Serial @ 9600 baud
  Serial.flush();       // Clear  buffer
  strip.begin(); // Start neopixel library
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  if (Serial.available() > 0) {        // Check buffer
    newData = Serial.read();            // Save string received
    Serial.flush();                    // Clear buffer

    switch (newData) {

      case 'a':                        // Idle vertical
        //idleV();
        Serial.println("IDLE-VERT-TESTING");
        strip.setPixelColor(0, 255, 0, 0);
        strip.show();
        break;


      case 'b':  //Idle horizontal
        //idleH();
        Serial.println("IDLE-HORIZ-TESTING");
        strip.setPixelColor(0, 0, 255, 0);
        strip.show();
        break;

      case 'c':                        // Intake
        //intake();
        Serial.println("INTAKE-TESTING");
        //intake dd and norm
        if (dropDriveState == 1) {
          strip.setPixelColor(0, 255, 0, 0);
          strip.show();
        } else {
          strip.setPixelColor(0, 0, 0, 255);
          strip.show();
        }
        break;



      case 'd':                        // Deploy
        //deploy();
        Serial.println("DEPLOY-TESTING");
        //we need an deploy dd and norm
        if (dropDriveState == 1) {
          strip.setPixelColor(0, 255, 155, 0);
          strip.show();
        } else {
          strip.setPixelColor(0, 99, 0, 255);
          strip.show();
        }
        break;



      case 'e':                        // Drop Drive Down
        //dropDrive();
        Serial.println("DRIVE-TdESTING");
        dropDriveState = 1; // allows the others to use the horizontal strip for drop drive while drop drive is active
        strip.setPixelColor(0, 255, 255, 255);
        strip.show();

        break;



      case 'f':                        // Drop Drive Up
        //dropDrive();
        Serial.println("DRIVE-UP-TESTING");
        dropDriveState = 0; // gives full access to the horizontal strip while drop drive is inactive
        break;



      case 'g':                        // Elevator Up
        //elev();
        Serial.println("ELEV-TESTING");

        strip.setPixelColor(1, 0, 255, 255);
        strip.show();

        break;


      case 'h':                        // Winch
        //winch();
        Serial.println("WINCH-TESTING");
        strip.setPixelColor(1, 0, 0, 255);
        strip.show();
        break;


      case 'i':                        // Off
          Serial.println("OFF-TESTING");
          break;


        default:
          Serial.print("Error: Unexpected command");
      }
    }
  }

