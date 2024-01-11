import RPi.GPIO as GPIO
from time import sleep
import time
import random

class MotorController:
    def __init__(self, in1, in2, en_a, in3, in4, en_b):
        self.in1 = in1
        self.in2 = in2
        self.en_a = en_a
        self.in3 = in3
        self.in4 = in4
        self.en_b = en_b

        GPIO.setwarnings(False)
        GPIO.setmode(GPIO.BCM)

        # Setup the GPIO pins
        GPIO.setup(self.in1, GPIO.OUT)
        GPIO.setup(self.in2, GPIO.OUT)
        GPIO.setup(self.en_a, GPIO.OUT)

        GPIO.setup(self.in3, GPIO.OUT)
        GPIO.setup(self.in4, GPIO.OUT)
        GPIO.setup(self.en_b, GPIO.OUT)

        self.pwm_a = GPIO.PWM(self.en_a, 100)
        self.pwm_b = GPIO.PWM(self.en_b, 100)
        self.pwm_a.start(75)
        self.pwm_b.start(75)

    def start(self):
        # Method to start the vehicle
        print("Vehicle started")

    def stop(self):
        # Method to stop the vehicle
        GPIO.output(self.in1, GPIO.LOW)
        GPIO.output(self.in2, GPIO.LOW)
        GPIO.output(self.in4, GPIO.LOW)
        GPIO.output(self.in3, GPIO.LOW)
        print("Vehicle stopped")

    def move_forward(self):
        GPIO.output(self.in1, GPIO.HIGH)
        GPIO.output(self.in2, GPIO.LOW)
        GPIO.output(self.in4, GPIO.HIGH)
        GPIO.output(self.in3, GPIO.LOW)
        print("Moving forward")

    def move_backward(self):
        GPIO.output(self.in1, GPIO.LOW)
        GPIO.output(self.in2, GPIO.HIGH)
        GPIO.output(self.in4, GPIO.LOW)
        GPIO.output(self.in3, GPIO.HIGH)
        print("Moving backward")

    def move_left(self):
        GPIO.output(self.in1, GPIO.HIGH)
        GPIO.output(self.in2, GPIO.LOW)
        GPIO.output(self.in4, GPIO.LOW)
        GPIO.output(self.in3, GPIO.LOW)
        print("Turning left")

    def move_right(self):
        GPIO.output(self.in1, GPIO.LOW)
        GPIO.output(self.in2, GPIO.HIGH)
        GPIO.output(self.in4, GPIO.LOW)
        GPIO.output(self.in3, GPIO.LOW)
        print("Turning right")

    def cleanup(self):
        # Clean up the GPIO settings
        GPIO.cleanup()
        print("GPIO Cleaned up")
    
    def random_walk(self, duration, step_time):
        start_time = time.time()
        while time.time() - start_time < duration:
            action = random.choice(["forward", "backward", "left", "right", "stop"])
            if action == "forward":
                self.move_forward()
            elif action == "backward":
                self.move_backward()
            elif action == "left":
                self.move_left()
            elif action == "right":
                self.move_right()
            elif action == "stop":
                self.stop()
            time.sleep(step_time)

def mannual_control():
    # Example usage
    try:
        # Initialize the motor controller with GPIO pin numbers
        motor_controller = MotorController(17, 27, 4, 5, 6, 13)

        # Example: Start the vehicle
        motor_controller.start()

        # Replace this with your own logic to control the vehicle
        while True:
            command = input("Enter command: ")
            if command == 'w':
                motor_controller.move_forward()
            elif command == 's':
                motor_controller.move_backward()
            elif command == 'a':
                motor_controller.move_left()
            elif command == 'd':
                motor_controller.move_right()
            elif command == 'c':
                motor_controller.stop()

    except KeyboardInterrupt:
        motor_controller.cleanup()

def random_walk():
    # Example usage
    try:
        # Initialize the motor controller with GPIO pin numbers
        motor_controller = MotorController(17, 27, 4, 5, 6, 13)
        motor_controller.start()

        # Perform random walk for a total duration of 60 seconds, with each step lasting 5 seconds
        motor_controller.random_walk(duration=60, step_time=5)

    except KeyboardInterrupt:
        motor_controller.cleanup()