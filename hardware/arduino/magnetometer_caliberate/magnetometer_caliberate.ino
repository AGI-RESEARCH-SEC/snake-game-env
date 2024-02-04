#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>

int motor_lA = 8;
int motor_lB = 9;
int motor_enableA = 10;

int motor_rA = 3;
int motor_rB = 4;
int motor_enableB = 5;
float initialDirection = 85;
float leftAngle = 147;
float rightAngle = 22;
float northAngle = 0;
float westAngle = 111;
float southAngle = 256;
float eastAngle = 216;
float DeviationThreshold = 10.0;

// Global variables for calibration
float xOffset = 0.0;
float yOffset = 0.0;
float zOffset = 0.0;
float xScale = 1.0;
float yScale = 1.0;
float zScale = 1.0;

/* Assign a unique ID to this sensor at the same time */
Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);


void displaySensorDetails(void)
{
  sensor_t sensor;
  mag.getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" uT");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" uT");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" uT");  
  Serial.println("------------------------------------");
  Serial.println("");
  delay(500);
}

// Function to get calibrated magnetic sensor coordinates
void getCalibratedMagneticCoordinates(float &x, float &y, float &z) {
  sensors_event_t event;
  mag.getEvent(&event);
  x = event.magnetic.x;
  y = event.magnetic.y;
  z = event.magnetic.z;

  // Apply calibration
  x = (x - xOffset) * xScale;
  y = (y - yOffset) * yScale;
  z = (z - zOffset) * zScale;
}

// Function to get magnetic sensor heading
float getMagneticHeading() {
  float x, y, z;
  getCalibratedMagneticCoordinates(x, y, z);

  Serial.print("X: "); Serial.print(x); Serial.print("  ");
  Serial.print("Y: "); Serial.print(y); Serial.print("  ");
  Serial.print("Z: "); Serial.print(z); Serial.print("  ");
  Serial.println("uT");

  float heading = atan2(y, x);
  float headingDegrees;
  if (heading < 0){
    heading += 2 * PI;
    headingDegrees = heading * (180 / PI);
    Serial.print("0. Heading (degrees): "); Serial.println(headingDegrees);
  } else if(heading > 2 * PI){
    heading -= 2 * PI;
    headingDegrees = heading * (180 / PI);
    Serial.print("1. Heading (degrees): "); Serial.println(headingDegrees);
  } else {
    headingDegrees = heading * (180 / PI);
    Serial.print("2. Heading (degrees): "); Serial.println(headingDegrees);
  }

  return headingDegrees;
}

void calibrateMagnetometer() {
  float x, y, z;

  // Collect calibration data (manually input or read from a file)
  float minX = -25; // replace with your actual values
  float maxX = 19.7;  // replace with your actual values
  float minY = -19.55; // replace with your actual values
  float maxY = 25.36;  // replace with your actual values
  float minZ = -0.1; // replace with your actual values
  float maxZ = 28.06;  // replace with your actual values

  // Calculate offsets
  xOffset = (maxX + minX) / 2.0;
  yOffset = (maxY + minY) / 2.0;
  zOffset = (maxZ + minZ) / 2.0;

  // Calculate scale factors
  xScale = 2.0 / (maxX - minX);
  yScale = 2.0 / (maxY - minY);
  zScale = 2.0 / (maxZ - minZ);
}

// void displayHeadingEvery5Seconds() {
//   while (true) {
//     float heading_degrees = getMagneticHeading();
//     Serial.print("Heading (degrees): "); Serial.println(heading_degrees);
//     delay(5000);
//   }
// }

void setup() {
  pinMode(motor_lA, OUTPUT);
  pinMode(motor_lB, OUTPUT);
  pinMode(motor_enableA, OUTPUT);

  pinMode(motor_rA, OUTPUT);
  pinMode(motor_rB, OUTPUT);
  pinMode(motor_enableB, OUTPUT);

  Serial.begin(9600);

  Serial.println("HMC5883 Magnetometer Test");
  Serial.println("");

  if (!mag.begin()) {
    Serial.println("Ooops, no HMC5883 detected ... Check your wiring!");
    while (1);
  }

  displaySensorDetails();
  calibrateMagnetometer();  // Calibrate the magnetometer
}

void loop() {
  // displayHeadingEvery5Seconds();
  float heading_degrees = getMagneticHeading();

  delay(500);
}
