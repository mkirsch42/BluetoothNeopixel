import serial
from neopixel import *
import time

# LED strip configuration:
LED_COUNT      = 55      # Number of LED pixels.
LED_PIN        = 18      # GPIO pin connected to the pixels (must support PWM!).
LED_FREQ_HZ    = 800000  # LED signal frequency in hertz (usually 800khz)
LED_DMA        = 5       # DMA channel to use for generating signal (try 5)
LED_BRIGHTNESS = 64     # Set to 0 for darkest and 255 for brightest
LED_INVERT     = False   # True to invert the signal (when using NPN transistor level shift)

strip = Adafruit_NeoPixel(LED_COUNT, LED_PIN, LED_FREQ_HZ, LED_DMA, LED_INVERT, LED_BRIGHTNESS)
	# Intialize the library (must be called once before other functions).
strip.begin()
s = serial.Serial('/dev/rfcomm0')
while 1:
    token = s.read()
    if token == b'*':
        data = s.read(7)
        for i in range(144):
            strip.setPixelColor(i, Color(data[3], data[2], data[4]))
        strip.show()
