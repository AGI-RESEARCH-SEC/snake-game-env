# Part-7: Distance Sensor
"""
vcc: power      -> 2 5V
TRG: shoot out  -> 7 GPIO-4
ECHHO: input    -> 12 GPIO 18
Ground          -> 6 qGND
"""

# nano distance_sensor.py
# ```
import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BCM)

TRIG = 4
ECHO = 18

# Setup trigger and echo pin
GPIO.setup(TRIG, GPIO.OUT)
GPIO.setup(ECHO, GPIO.IN)

# 
GPIO.output(TRIG, True)
time.sleep(0.0001)
GPIO.output(TRIG, False)

while GPIO.input(ECHO) == False:
    start = time.time()

while GPIO.input(ECHO) == True:
    end = time.time()

sig_time = end-start

# cm:
distance = sig_time / 0.00058   # Inches: 0.000148
print(distance)
GPIO.cleanup()
# ```

# python distance_sensor.py
