#include <Adafruit_NeoPixel.h>

#define NEOPIXEL_PIN 2
#define NEOPIXEL_COUNT 40

#define START_CMD 42
#define END_CMD 4

#define OP_MASK  0b01111111
#define OP_COLOR 0b00000001
#define OP_RANGE 0b00000010
#define OP_ALL   0b00000011
#define OP_APPLY 0b10000000

#define MODE_BT 0
#define MODE_LISTEN 1

byte currentMode = MODE_BT;
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NEOPIXEL_COUNT, NEOPIXEL_PIN);

void setup() {
  Serial.begin(115200);
  Serial.setTimeout(100);
  pixels.begin();
  pixels.show();
}


void loop() {
  if(Serial.read() == START_CMD) {
    byte in[7];
    Serial.readBytes(in, 7);
    if(in[6] != END_CMD) {
      return;
    }
    byte op = in[0] & OP_MASK;
    switch(op) {
      case OP_COLOR:
        if(currentMode == MODE_BT) pixels.setPixelColor(in[1], in[2], in[3], in[4]);
        break;
      case OP_RANGE:
        if(currentMode == MODE_BT) range(in[1], in[5], in[2], in[3], in[4]);
        break;
      case OP_ALL:
        if(currentMode == MODE_BT) range(0, NEOPIXEL_COUNT - 1, in[2], in[3], in[4]);
        break;
    }
    if(in[0] & OP_APPLY) {
      apply();
    }
    //Serial.write(6);
  }
  //if(currentMode == MODE_LISTEN) listenMode();
}

unsigned long lastUpdate = 0;
#define REFRESH_PERIOD 16667
void apply() {
  unsigned long now = micros();
  unsigned long since = now - lastUpdate;
  if(since < REFRESH_PERIOD) {
    delayMicroseconds(REFRESH_PERIOD - since);
  }
  pixels.show();
  lastUpdate = micros();
}

void range(byte s, byte e, byte r, byte g, byte b) {
  for(byte n = s; n <= e; n++) {
    pixels.setPixelColor(n, r, g, b);
  }
}

/*
int peak = 0;
long peakTime = 0;
byte[] listenColor = {255, 255, 255};
#define LISTEN_PEAK_THRESHOLD 170
void listenMode() {
  int in = analogRead(0);
  int pixels = round((NEOPIXEL_COUNT/(float)1024) * in);
  range(0, pixels, listenColor[0], listenColor[1], listenColor[2]);
  pixels.show();
}
*/
