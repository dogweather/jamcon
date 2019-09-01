#include <Adafruit_NeoPixel.h>

const int NEO_PIXEL_COUNT = 12;
const int NEO_PIXEL_PIN = 3;           // Output pin for neo pixels.
const int POWER_LED_PIN = 13;          // Output pin for power LED (pin 13 to use Teensy 3.0's onboard LED).
const int DELAY = 30;
const int STEPS = 10;

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NEO_PIXEL_COUNT+1, NEO_PIXEL_PIN, NEO_GRB + NEO_KHZ800);

const int r1 = 0;
const int g1 = 0;
const int b1 = 200;

const int r2 = 0;
const int g2 = 0;
const int b2 = 0;


void setup() {
  // Turn on the power indicator LED.
//  pinMode(POWER_LED_PIN, OUTPUT);
  digitalWrite(POWER_LED_PIN, HIGH);
  
  // Initialize neo pixel library and turn off the LEDs
  pixels.begin();
  pixels.setBrightness(25);
  pixels.clear();
  pixels.setPixelColor(NEO_PIXEL_COUNT, 200,0,0);
  pixels.show();
}


void loop() {
  for( int hot_pixel = 0; hot_pixel < NEO_PIXEL_COUNT * STEPS; hot_pixel++) {
    float position = 1.0 * hot_pixel / STEPS;
    
    // Background color
    pixels.fill(pixels.Color(r2, g2, b2));
    pixels.setPixelColor(NEO_PIXEL_COUNT, 200,0,0);

    int p1 = (int) position;
    int p2 = (p1 + 1) % NEO_PIXEL_COUNT;
    int p3 = (p1 + 2) % NEO_PIXEL_COUNT;

    float distance = position - p1;
    float fraction_bg = distance;
    float fraction_fg = 1.0 - distance;
    
    // Red "out of tune" color
    pixels.setPixelColor(p1, r2 * fraction_bg + r1 * fraction_fg, g2 * fraction_bg + g1 * fraction_fg, b2 * fraction_bg + b1 * fraction_fg);
    pixels.setPixelColor(p3, r2 * fraction_fg + r1 * fraction_bg, g2 * fraction_fg + g1 * fraction_bg, b2 * fraction_fg + b1 * fraction_bg);
    pixels.setPixelColor(p2, r1, g1, b1);

    pixels.show();
    delay(DELAY);
  }
}
