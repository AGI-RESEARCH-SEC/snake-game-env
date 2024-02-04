#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>


// -------------
// Motor code 
// -------------
const int numMeasurements = 3; // 5 // Number of ultrasonic sensor measurements to average
int continuous_actions = 1; // 0 Represent Delay after each action; 1 Represent Discrete actions
bool use_magnetometer_for_turning = true; // 0 is off. 1 is on. 
bool magnetometer_continuous_rotation = false;
float magnetometer_deviation_threshold = 20.0; // angle (degrees) deviation threshold


// angles for cardinal directions
float northAngle = 160; // 0;
float westAngle = 87;  // 111;
float southAngle =  330; // 256
float eastAngle = 212;    // 216


int motor_lA = 8;
int motor_lB = 9;
int motor_enable_left = 10;

int motor_rA = 3;
int motor_rB = 4;
int motor_enable_right = 5;

void Stop() {
  Serial.println("Stop");
  digitalWrite(motor_lA, LOW);
  digitalWrite(motor_lB, LOW);
  digitalWrite(motor_rA, LOW);
  digitalWrite(motor_rB, LOW);
  // delay(300);
}
void forward(int delay_parameter = 1000, bool forward_after_turning = false) {
  Serial.println("Forward");
  digitalWrite(motor_lA, HIGH);
  digitalWrite(motor_lB, LOW);
  digitalWrite(motor_rA, LOW);
  digitalWrite(motor_rB, HIGH);

  if ((continuous_actions == 0) || (forward_after_turning == 1)){
    // Discrete actions
    delay(delay_parameter);
    Stop();
  }
  return;
}

void right(int delay_parameter = 1020, bool move_forward=1) {// 1200
  Serial.println("Right");
  digitalWrite(motor_lA, HIGH);
  digitalWrite(motor_lB, LOW);
  digitalWrite(motor_rA, HIGH);
  digitalWrite(motor_rB, LOW);
  if (magnetometer_continuous_rotation != 1){
    delay(delay_parameter);
    Stop();
  }
  if (move_forward == 1){
    forward();
  }
}

void left(int delay_parameter = 1000, bool move_forward=1) {// 1250
  Serial.println("Left");
  Serial.println(delay_parameter);
  digitalWrite(motor_lA, LOW);
  digitalWrite(motor_lB, HIGH);
  digitalWrite(motor_rA, LOW);
  digitalWrite(motor_rB, HIGH);
  if (magnetometer_continuous_rotation != 1){
    delay(delay_parameter);
    Stop();
  }
  if (move_forward == 1){
    forward();
  }
}


// Function to get the nearest cardinal direction
float getNearestDirection(float currentAngle) {
    // Calculate the angular difference from each cardinal direction
    float diffNorth = fabs(currentAngle - northAngle);
    float diffSouth = fabs(currentAngle - southAngle);
    float diffEast = fabs(currentAngle - eastAngle);
    float diffWest = fabs(currentAngle - westAngle);

    // Find the minimum difference using a ternary operator
    float minDiff = (diffNorth < diffSouth) ? diffNorth : diffSouth;
    minDiff = (diffEast < minDiff) ? diffEast : minDiff;
    minDiff = (diffWest < minDiff) ? diffWest : minDiff;

    // Determine the nearest direction based on the minimum difference
    if (minDiff == diffNorth) {
        Serial.print("north it is");
        return northAngle;

    } else if (minDiff == diffSouth) {
        Serial.println("south it is");
        return southAngle;
    } else if (minDiff == diffEast) {
        Serial.println("east it is");
        return eastAngle;
    } else {
        Serial.println("west it is");
        return westAngle;
    }
}

// Function to rotate towards the target direction
void turn_using_magnetometer(int action, bool forward_at_end = false) {
  //actions: [0, 1, 2] represent ["left", "right", "forward"] respectively
  float target_degrees;
  float heading_degrees;
  float deviation_left;
  float deviation_right;
  float deviation;
  // Serial.println("======================");Serial.println("Moving ");Serial.println(action);Serial.println("======================");
  heading_degrees = getMagneticHeading();// getMagneticHeading();
  heading_degrees = fmod(heading_degrees, 360.0);
  if (action == 0) {
    target_degrees = getNearestDirection(fabs(heading_degrees-90));
    /*
      target_degrees = initialDirection - 90;
      // it should have worked but the dirfference deviates from 90Degrees (East, West, North, South)
    */
    // Serial.println("======================");Serial.println("mag. Left");Serial.println("======================");
  } else if (action == 1) {
    target_degrees = getNearestDirection(fabs(heading_degrees+90));
    /*
      target_degrees = initialDirection + 90;
      // it should have worked but the dirfference deviates from 90Degrees (East, West, North, South)
    */
    
    // Serial.println("======================");Serial.println("mag. Right");Serial.println();Serial.println("======================");
  } else if (action == 2) {
    Serial.println("======================");Serial.println("mag. Forward");Serial.println("======================");
    forward();  // move forward
    return;
  }
  deviation_left = fmod(fmod(heading_degrees - target_degrees, 360.0)+360, 360);  // deviation from 
  deviation_right = fmod(fmod(target_degrees - heading_degrees, 360.0)+360, 360);
  deviation = min(deviation_left, deviation_right);
  //  float targetDirection = 97.0;  // Assuming the target direction is 90 degrees (east)
  //  float targetDirectionError = 20.0;
  while (deviation > magnetometer_deviation_threshold) {
    // delay(1000);
    // Get magnetic heading angle in degrees
    heading_degrees = getMagneticHeading();

    // Check if the car is not facing towards the target direction
    heading_degrees = fmod(heading_degrees, 360.0);
    //  float deviation_left = fmod(abs(heading_degrees - target_degrees), 360.0);
    //  float deviation_right = fmod(abs(target_degrees - heading_degrees), 360.0);
    /*
        * `fmod(-3, 4)` gives -3
        * the work-around is: `fmod(fmod(-3, 4) + 4, 4)` which gives 1
        * for positive numbers, the functionality is same as using single fmod. e.g. fmod(fmod(3, 4) + 4, 4) gives 3.
      
    */
    float deviation_left = fmod(fmod(heading_degrees - target_degrees, 360.0)+360, 360);
    float deviation_right = fmod(fmod(target_degrees - heading_degrees, 360.0)+360, 360);
    float deviation = min(deviation_left, deviation_right);
  
    Serial.print("Heading : "); Serial.println(heading_degrees);
    Serial.print("Target : "); Serial.println(target_degrees);
    Serial.print("deviation_left: ");  Serial.println(deviation_left);
    Serial.print("deviation_right: ");  Serial.println(deviation_right);
    Serial.print("deviation: ");  Serial.println(deviation);
    Serial.println("\n\n");
  //  Serial.print("deviation3: ");  Serial.println(deviation3);
  //  Serial.print("deviation4: ");  Serial.println(deviation4);

    if (deviation > magnetometer_deviation_threshold) {
      // Adjust the relationship between deviation and duration based on your requirements
      int duration = map(deviation, 0, 180, 5, 200); // map(deviation, 0, 180, 200, 2000)
      /* -------
          map:
         -------
        deviation: This is the value you want to map, in this case, it's the deviation angle.
        0: This is the lower bound of the original range. In this context, it assumes that deviation can range from 0 to 180 degrees.
        180: This is the upper bound of the original range. It indicates the maximum possible value for the deviation variable.
        50: This is the lower bound of the target range. It represents the minimum value you want to map deviation to.
        2000: This is the upper bound of the target range. It represents the maximum value 
      */
      if (deviation_left < deviation_right) {
        // If deviation is positive, move left
        Serial.println("======================");Serial.print("mag. Right. ");Serial.print(heading_degrees);Serial.print(" -----> ");Serial.println(target_degrees);Serial.println(duration);Serial.println("======================");
        right(duration, 0);
      } else {
        // If deviation is negative, move right
        Serial.println("======================");Serial.print("mag. Left. ");Serial.print(heading_degrees);Serial.print(" -----> ");Serial.println(target_degrees);Serial.println(duration);Serial.println("======================");
        left(duration, 0);
      }
    } else {
      // deviation is less than magnetometer_deviation_threshold.
      break;
    }
  }
  // deviation is less than magnetometer_deviation_threshold.
  if (forward_at_end != 1){
    // stop at the end of turning
    Stop();
  } else {
    // move forward at the end of turning
    forward(1000, 1);
  }
  return;
}

























// int motor_lA = 8;
// int motor_lB = 9;
// int motor_enableA = 10;

// int motor_rA = 3;
// int motor_rB = 4;
int motor_enableB = 5;
float initialDirection = 85;
float leftAngle = 147;
float rightAngle = 22;
// float northAngle = 0;
// float westAngle = 111;
// float southAngle = 256;
// float eastAngle = 216;
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
// put your setup code here, to run once:
  pinMode(motor_lA,OUTPUT);   //left motors forward
  pinMode(motor_lB,OUTPUT);   //left motors reverse
  pinMode(motor_enable_left, OUTPUT);   // optional

  pinMode(motor_rA,OUTPUT);   //right motors forward
  pinMode(motor_rB,OUTPUT);   //rignt motors reverse
  pinMode(motor_enable_right, OUTPUT);   // optional

  analogWrite(motor_enable_left, 210);  // 90
  analogWrite(motor_enable_right, 200);  // 100

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
  // float heading_degrees = getMagneticHeading();
  turn_using_magnetometer(0);
  // right();
  delay(10000);
}
