#include <Adafruit_NeoPixel.h>

#define NEOPIXEL_PIN 2

#define START_CMD 42

#define OP_COLOR 0b00000001
#define OP_APPLY 0b10000000

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(40, NEOPIXEL_PIN);

void setup() {
  Serial.begin(115200);
  Serial.setTimeout(60000);
  pixels.begin();
  pixels.show();
}

void loop() {
  if(Serial.read() == START_CMD) {
    byte in[7];
    Serial.readBytes(in, 7);
    byte op = in[0];
    if(op & OP_COLOR) {
      pixels.setPixelColor(in[1], in[2], in[3], in[4]);
    }
    if(op & OP_APPLY) {
      pixels.show();
    }
  }
}

