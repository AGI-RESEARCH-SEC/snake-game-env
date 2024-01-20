const int leftTrigPin = 2;   // Trigger pin for the left ultrasonic sensor
const int leftEchoPin = 3;   // Echo pin for the left ultrasonic sensor

const int rightTrigPin = 4;  // Trigger pin for the right ultrasonic sensor
const int rightEchoPin = 5;  // Echo pin for the right ultrasonic sensor

const int motor_lA = 8;  // Left motor control pin
const int motor_lB = 9;  // Left motor control pin
const int motor_enableA = 10; // PWM control for left motor speed

const int motor_rA = 11; // Right motor control pin
const int motor_rB = 12; // Right motor control pin
const int motor_enableB = 6;  // PWM control for right motor speed

const int targetDistance = 20;  // Target distance from the obstacle (adjust as needed)
const int maxSpeed = 255;  // Maximum motor speed

void setup() {
  Serial.begin(9600);
  
  pinMode(leftTrigPin, OUTPUT);
  pinMode(leftEchoPin, INPUT);
  pinMode(rightTrigPin, OUTPUT);
  pinMode(rightEchoPin, INPUT);
  
  pinMode(motor_lA, OUTPUT);
  pinMode(motor_lB, OUTPUT);
  pinMode(motor_enableA, OUTPUT);
  pinMode(motor_rA, OUTPUT);
  pinMode(motor_rB, OUTPUT);
  pinMode(motor_enableB, OUTPUT);
}

void loop() {
  // Measure distances from left and right ultrasonic sensors
  int leftDistance = measureDistance(leftTrigPin, leftEchoPin);
  int rightDistance = measureDistance(rightTrigPin, rightEchoPin);

  // Calculate the error (difference between right and left distances)
  int error = rightDistance - leftDistance;

  // Adjust motor speeds based on the error
  int leftSpeed = constrain(maxSpeed - error, 0, maxSpeed);
  int rightSpeed = constrain(maxSpeed + error, 0, maxSpeed);

  // Apply speeds to the motors
  analogWrite(motor_enableA, leftSpeed);
  digitalWrite(motor_lA, HIGH);
  digitalWrite(motor_lB, LOW);

  analogWrite(motor_enableB, rightSpeed);
  digitalWrite(motor_rA, HIGH);
  digitalWrite(motor_rB, LOW);
}

int measureDistance(int trigPin, int echoPin) {
  // Measure distance using ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  return pulseIn(echoPin, HIGH) * 0.034 / 2;
}
