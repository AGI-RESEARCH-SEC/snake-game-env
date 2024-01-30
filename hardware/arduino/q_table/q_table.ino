#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>

int motor_lA = 8;
int motor_lB = 9;
int motor_enableA = 10;

int motor_rA = 3;
int motor_rB = 4;
int motor_enableB = 5;
float initialDirection = 85; //(85 for IT class facing white-board) 100.0; // angle (degrees) for initial direction
float leftAngle = 147;
float rightAngle = 22;
float DeviationThreshold = 10.0; // angle (degrees) deviation threshold
/* Assign a unique ID to this sensor at the same time */
Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);

void displaySensorDetails(void) {
  sensor_t sensor;
  mag.getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.print("Sensor:       "); Serial.println(sensor.name);
  Serial.print("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" uT");
  Serial.print("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" uT");
  Serial.print("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" uT");
  Serial.println("------------------------------------");
  Serial.println("");
  delay(500);
}

// Function to get magnetic sensor coordinates
void getMagneticCoordinates(float &x, float &y, float &z) {
  sensors_event_t event;
  mag.getEvent(&event);
  x = event.magnetic.x;
  y = event.magnetic.y;
  z = event.magnetic.z;
}

// Function to get magnetic sensor heading
float getMagneticHeading() {
  float x, y, z;
  getMagneticCoordinates(x, y, z);
    // Display the results (magnetic vector values are in micro-Tesla (uT))
  Serial.print("X: "); Serial.print(x); Serial.print("  ");
  Serial.print("Y: "); Serial.print(y); Serial.print("  ");
  Serial.print("Z: "); Serial.print(z); Serial.print("  ");
  Serial.println("uT");
  float heading = atan2(y, x);

  // Once you have your heading, you must then add your 'Declination Angle', which is the 'Error' of the magnetic field in your location.
  // Find yours here: http://www.magnetic-declination.com/
  // Mine is: -13* 2' W, which is ~13 Degrees, or (which we need) 0.22 radians
  // If you cannot find your Declination, comment out these two lines, your compass will be slightly off.
  // float declinationAngle = 0.22;
  // heading += declinationAngle;

  // Correct for when signs are reversed.
  if (heading < 0)
    heading += 2 * PI;

  // Check for wrap due to addition of declination.
  if (heading > 2 * PI)
    heading -= 2 * PI;

  // Convert radians to degrees for readability.
  float headingDegrees = heading * 180 / PI;

  return headingDegrees;
}

void left(int delay_parameter = 1900, bool move_forward=0) {
  Serial.println("Left");
  digitalWrite(motor_lA, HIGH);
  digitalWrite(motor_lB, LOW);
  digitalWrite(motor_rA, HIGH);
  digitalWrite(motor_rB, LOW);
  delay(delay_parameter);
  Stop();
  if (move_forward == 1){
    forward();
  }
}

void forward() {
  Serial.println("Forward");
  digitalWrite(motor_lA, HIGH);
  digitalWrite(motor_lB, LOW);
  digitalWrite(motor_rA, LOW);
  digitalWrite(motor_rB, HIGH);
  delay(1500);
  Stop();
}

void back() {
  Serial.println("Back");
  digitalWrite(motor_lA, LOW);
  digitalWrite(motor_lB, HIGH);
  digitalWrite(motor_rA, HIGH);
  digitalWrite(motor_rB, LOW);
  delay(3000);
  Stop();
}

void right(int delay_parameter = 1750, bool move_forward=0) {
  Serial.println("Right");
  Serial.println(delay_parameter);
  digitalWrite(motor_lA, LOW);
  digitalWrite(motor_lB, HIGH);
  digitalWrite(motor_rA, LOW);
  digitalWrite(motor_rB, HIGH);
  delay(delay_parameter);
  Stop();
}

void Stop() {
  Serial.println("Stop");
  digitalWrite(motor_lA, LOW);
  digitalWrite(motor_lB, LOW);
  digitalWrite(motor_rA, LOW);
  digitalWrite(motor_rB, LOW);
  delay(300);
}


// Function to rotate towards the target direction
void move_it(int action) {
  //actions: [0, 1, 2] represent ["left", "right", "forward"] respectively
  float target_degrees;
  float heading_degrees;
  float deviation1;
  float deviation2;
  float deviation;
  Serial.println("======================");Serial.println("Moving ");Serial.println(action);Serial.println("======================");
   if (action == 0) {
    target_degrees = initialDirection + 90;   // rotate left
    target_degrees = leftAngle;
    Serial.println("======================");Serial.println("Moving Left");Serial.println("======================");
  } else if (action == 1) {
    target_degrees = initialDirection - 90;   // rotate right
    target_degrees = rightAngle; //
    Serial.println("======================");Serial.println("Moving Right");Serial.println("======================");
  } else if (action == 2) {
    Serial.println("======================");Serial.println("Moving Forward");Serial.println("======================");
    forward();  // move forward
    return;
  }


  heading_degrees = getMagneticHeading();
  heading_degrees = fmod(heading_degrees, 360.0);
  deviation1 = fmod(fmod(heading_degrees - target_degrees, 360.0)+360, 360);
  deviation2 = fmod(fmod(target_degrees - heading_degrees, 360.0)+360, 360);
  deviation = min(deviation1, deviation2);
  //  float targetDirection = 97.0;  // Assuming the target direction is 90 degrees (east)
  //  float targetDirectionError = 20.0;
  while (deviation > DeviationThreshold) {
    // delay(500);
    // Get magnetic heading angle in degrees
    heading_degrees = getMagneticHeading();
    
    // Check if the car is not facing towards the target direction
    heading_degrees = fmod(heading_degrees, 360.0);
    //  float deviation1 = fmod(abs(heading_degrees - target_degrees), 360.0);
    //  float deviation2 = fmod(abs(target_degrees - heading_degrees), 360.0);
    /*
        * `fmod(-3, 4)` gives -3
        * the work-around is: `fmod(fmod(-3, 4) + 4, 4)` which gives 1
        * for positive numbers, the functionality is same as using single fmod. e.g. fmod(fmod(3, 4) + 4, 4) gives 3.
      
    */
    float deviation1 = fmod(fmod(heading_degrees - target_degrees, 360.0)+360, 360);
    float deviation2 = fmod(fmod(target_degrees - heading_degrees, 360.0)+360, 360);
    float deviation = min(deviation1, deviation2);
  
    Serial.print("Heading : "); Serial.println(heading_degrees);
    Serial.print("Target : "); Serial.println(target_degrees);
    Serial.print("deviation1: ");  Serial.println(deviation1);
    Serial.print("deviation2: ");  Serial.println(deviation2);
    Serial.print("deviation: ");  Serial.println(deviation);
    Serial.println("\n\n");
  //  Serial.print("deviation3: ");  Serial.println(deviation3);
  //  Serial.print("deviation4: ");  Serial.println(deviation4);
  
    if (deviation > DeviationThreshold) {
      // Adjust the relationship between deviation and duration based on your requirements
      int duration = map(deviation, 0, 180, 10, 450); // 200,2000
      /*
        deviation: This is the value you want to map, in this case, it's the deviation angle.
        0: This is the lower bound of the original range. In this context, it assumes that deviation can range from 0 to 180 degrees.
        180: This is the upper bound of the original range. It indicates the maximum possible value for the deviation variable.
        50: This is the lower bound of the target range. It represents the minimum value you want to map deviation to.
        2000: This is the upper bound of the target range. It represents the maximum value 
      */
  
      if (deviation1 < deviation2) {
        // If deviation is positive, move left
        left(duration);
      } else {
        // If deviation is negative, move right
        right(duration);
      }
    }
    else {
      return;
      // delay(1000);
    }
  }
  return;
}

void setup() {
  pinMode(motor_lA, OUTPUT);   // left motors forward
  pinMode(motor_lB, OUTPUT);   // left motors reverse
  pinMode(motor_enableA, OUTPUT);   // optional

  pinMode(motor_rA, OUTPUT);   // right motors forward
  pinMode(motor_rB, OUTPUT);   // right motors reverse
  pinMode(motor_enableB, OUTPUT);   // optional
  
 Serial.print("Initial Direction (degrees): "); Serial.println(initialDirection);
  // ==========================================
  // ============= Magnetometer ===============
  // ==========================================

  Serial.println("HMC5883 Magnetometer Test");
  Serial.println("");
  /* Initialise the sensor */
  if (!mag.begin()) {
    /* There was a problem detecting the HMC5883 ... check your connections */
    Serial.println("Ooops, no HMC5883 detected ... Check your wiring!");
    while (1);
  }
  /* Display some basic information on this sensor */
  displaySensorDetails();
 // ==========================================


  Serial.begin(9600);  // Initialize serial communication
}


void loop() {
//  Serial.print("Initial Direction (degrees): "); Serial.println(initialDirection);
  // float initialDirection = 100.0;
  float right_angle = fmod((initialDirection - 90.0), 360.0);
  float left_angle = fmod((initialDirection + 90.0), 360.0);
  //(Optional)
  analogWrite(motor_enableA, 180);//90
  analogWrite(motor_enableB, 200);//100
// ===========================================================================
//  Serial.print("turn left"); 
//  left();
//  delay(5000);
//  right();
//  delay(5000);  // Sleep for 5 seconds

//  Serial.print("Heading (degrees): "); Serial.println(headingDegrees);

  // Set your target direction (adjust as needed)
//  float targetDirection = 97.0;  // Assuming the target direction is 90 degrees (east)
//  float targetDirectionError = 20.0;

//  rotate(initialDirection, headingDegrees, targetDirectionError);
//move_it(0);  //actions: [0, 1, 2] are ["left", right, forward respectively]
//delay(5000);
//move_it(1);  //actions: [0, 1, 2] are ["left", right, forward respectively]
//delay(5000);
move_it(0);  //actions: [0, 1, 2] are ["left", right, forward respectively]
// delay(5000);
// move_it(1);  //actions: [0, 1, 2] are ["left", right, forward respectively]
// delay(5000);
// move_it(2);  //actions: [0, 1, 2] are ["left", right, forward respectively]

// move_it(2);
//// ===========================================================================

  
//  
  
  
//    // Move left for 3 seconds
//  left();
//  delay(5000);  // Sleep for 5 seconds
//
//  // Move right for 3 seconds
//  right();
//  delay(5000);  // Sleep for 5 seconds
//  
//  // Move forward for 3 seconds
//  forward();
//  delay(5000);  // Sleep for 5 seconds
//  
//  // Move back for 3 seconds
//  back();
//  delay(5000);  // Sleep for 5 seconds
//
//
//  delay(7000);

  
}
