# Part-8: Garage Stop Light
# nano garage_light.py

# ```
import RPi.GPIO as GPIO
import time

# cause breaking  the loop, pins will not get fully cleaned up.
GPIO.setwarnings(False)
GPIO.cleanup()
GPIO.setmode(GPIO.BCM)

TRIG1 = 4
ECHO1 = 18

TRIG2 = 23
ECHO2 = 24


# Setup trigger and echo pin
GPIO.setup(TRIG1, GPIO.OUT)
GPIO.setup(TRIG2, GPIO.OUT)
GPIO.setup(ECHO1, GPIO.IN)
GPIO.setup(ECHO2, GPIO.IN)



def each_distance(TRIG, ECHO):
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
    # print('Distance: {} cm'.format(distance))
    return distance

def get_distance():
    distance1 = each_distance(TRIG1, ECHO1)
    distance2 = each_distance(TRIG2, ECHO2)
    return {'distance1': distance1, 'distance2': distance2}

if __name__ == "__main__":
    while True:
        print(get_distance())
        time.sleep(1)
