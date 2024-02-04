#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>

const int numMeasurements = 3; // 5 // Number of ultrasonic sensor measurements to average
int continuous_actions = 1; // 0 Represent Delay after each action; 1 Represent Discrete actions
bool use_magnetometer_for_turning = true; // 0 is off. 1 is on. 
bool magnetometer_continuous_rotation = false;
float magnetometer_deviation_threshold = 12.0; // angle (degrees) deviation threshold

// Global variables for magnetometer calibration
float xOffset = 0.0;
float yOffset = 0.0;
float zOffset = 0.0;
float xScale = 1.0;
float yScale = 1.0;
float zScale = 1.0;

int left_threshold = 35;
int right_threshold = 35;
int front_threshold = 30;

// angles for cardinal directions
float northAngle = 160; //  178;
float westAngle = 87;   // 90;
float southAngle = 330;     // 13;
float eastAngle = 212;  // 310;
/* 
  // float initialDirection = 70;// 100.0; // angle (degrees) the bot is facing initially.
  // float initialDirection = 210;// college // angle (degrees) the bot is facing initially.
  Using {left_angle = initialDirection - 90, right=initialDirection+ 90} should have worked but difference between left-forward and right-forward differs from 90 Degrees.
*/

/* Assign a unique ID to this sensor at the same time */
Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);

int motor_lA = 8;
int motor_lB = 9;
int motor_enable_left = 10;

int motor_rA = 3;
int motor_rB = 4;
int motor_enable_right = 5;

// Ultrasonic Sesnsor
int trigger_left = A0;
int echo_left = A1;

int trigger_right = A2;
int echo_right = A3;

int trigger_front = 12; //A4;
int echo_front = 13;    //A5;

// Define the flattened Q-table copied from Python
//float flattened_q_table[] = {-0.14567542786524684, 0.028992119894766844, -0.2658059392757915, 15.500593710459835, -0.15679, -0.5751383360655641, -0.5, -0.7610600150158306, 19.256544264254092, 16.330889837828664, -2.594840781380889, -2.474224227054556, -0.852180077055561, -0.7006457235470309, 12.950534339413846, -2.2842125693118476, -2.776785077874974, -2.6859971955040907, -1.6150456834794744, -1.8485000844551536, 12.096579828480882, -2.7116605133971876, -3.133167873327339, -3.182911142097555};

// Maze-3: Obstacle Avoidance
float flattened_q_table[] = {0.0, 0.0, 0.0, -8.038707105143146, -8.082612249219368, -8.075357976574818, 0.0, 0.0, 0.0, -6.647911287348904, -8.350614717222712, -8.359131172256962, 0.0, 0.0, 0.0, -8.401727003925874, -7.051792274204917, -8.407046054870735, -8.05865436530638, -8.055914330703747, -7.195154863191697, -8.159045656801942, -8.353843068419978, -8.358464332980923};

// Define the number of states and actions
const int num_states = 8;  // 2^3
const int num_actions = 3;



// Create a 2D array to represent the Q-table
float q_table[num_states][num_actions];


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


// Binary to decimal
int binaryToDecimal(int input1, int input2, int input3) {
  // Convert binary to decimal
  int decimalValue = input1 * 4 + input2 * 2 + input3;
  return decimalValue;
}


// Gives Action with maximum q value
int findMaxAction(float q_values[], int num_actions) {
  // Find the index of the maximum value in the array
  int maxIndex = 0;
  for (int i = 1; i < num_actions; ++i) {
    if (q_values[i] > q_values[maxIndex]) {
      maxIndex = i;
    }
  }
  return maxIndex;
}


float getTargetAngle(float currentAngle, int direction) {
  // returns angle that would be final angle after rotation

  if ((southAngle >= currentAngle) && (eastAngle <= currentAngle)){
      // in between south and east
      if (direction == 0){
        // Left Turn
        return southAngle;
      } else{
        // Right Turn
        return eastAngle;
      }
    } else if((eastAngle >= currentAngle) && (northAngle <= currentAngle)){
      // in between North and West
      if (direction == 0){
        // Left Turn
        return eastAngle;
      } else{
        // Right Turn
        return northAngle;
      }
    } else if((northAngle >= currentAngle) && (westAngle <= currentAngle)){
      // in between North and West
      if (direction == 0){
        // Left Turn
        return northAngle;
      } else{
        // Right Turn
        return westAngle;
      }
    } else{
      // in between South and West
      if (direction == 0){
        // Left Turn
        return westAngle;
      } else{
        // Right Turn
        return southAngle;
      }
    }
}

// // Function to get the nearest cardinal direction
// float getNearestDirection(float currentAngle) {
//     // Calculate the angular difference from each cardinal direction
//     float diffNorth = fabs(currentAngle - northAngle);
//     float diffSouth = fabs(currentAngle - southAngle);
//     float diffEast = fabs(currentAngle - eastAngle);
//     float diffWest = fabs(currentAngle - westAngle);

//     // Find the minimum difference using a ternary operator
//     float minDiff = (diffNorth < diffSouth) ? diffNorth : diffSouth;
//     minDiff = (diffEast < minDiff) ? diffEast : minDiff;
//     minDiff = (diffWest < minDiff) ? diffWest : minDiff;

//     // Determine the nearest direction based on the minimum difference
//     if (minDiff == diffNorth) {
//         Serial.print("north it is");
//         return northAngle;

//     } else if (minDiff == diffSouth) {
//         Serial.println("south it is");
//         return southAngle;
//     } else if (minDiff == diffEast) {
//         Serial.println("east it is");
//         return eastAngle;
//     } else {
//         Serial.println("west it is");
//         return westAngle;
//     }
// }


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

void back() {
  Serial.println("Back");
  digitalWrite(motor_lA, LOW);
  digitalWrite(motor_lB, HIGH);
  digitalWrite(motor_rA, HIGH);
  digitalWrite(motor_rB, LOW);
  delay(3000);
  Stop();
}

void Stop() {
  Serial.println("Stop");
  digitalWrite(motor_lA, LOW);
  digitalWrite(motor_lB, LOW);
  digitalWrite(motor_rA, LOW);
  digitalWrite(motor_rB, LOW);
  // delay(300);
}





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

// Function to rotate towards the target direction
void turn_using_magnetometer(int action, bool forward_at_end = false) {
  //actions: [0, 1, 2] represent ["left", "right", "forward"] respectively
  float target_degrees;
  float heading_degrees;
  float deviation_left;
  float deviation_right;
  float deviation;
  // Serial.println("======================");Serial.println("Moving ");Serial.println(action);Serial.println("======================");
  heading_degrees = getMagneticHeading();
  heading_degrees = fmod(heading_degrees, 360.0);
  target_degrees = getTargetAngle(heading_degrees, action);
  // if (action == 0) {
  //   target_degrees = getNearestDirection(fabs(heading_degrees-90), action);
  //   /*
  //     target_degrees = initialDirection - 90;
  //     // it should have worked but the dirfference deviates from 90Degrees (East, West, North, South)
  //   */
  //   // Serial.println("======================");Serial.println("mag. Left");Serial.println("======================");
  // } else if (action == 1) {
  //   target_degrees = getNearestDirection(fabs(heading_degrees+90));
  //   /*
  //     target_degrees = initialDirection + 90;
  //     // it should have worked but the dirfference deviates from 90Degrees (East, West, North, South)
  //   */
    
  //   // Serial.println("======================");Serial.println("mag. Right");Serial.println();Serial.println("======================");
  // } else if (action == 2) {
  //   Serial.println("======================");Serial.println("mag. Forward");Serial.println("======================");
  //   forward();  // move forward
  //   return;
  // }
  deviation_left = fmod(fmod(heading_degrees - target_degrees, 360.0)+360, 360);  // deviation from 
  deviation_right = fmod(fmod(target_degrees - heading_degrees, 360.0)+360, 360);
  deviation = min(deviation_left, deviation_right);
  //  float targetDirection = 97.0;  // Assuming the target direction is 90 degrees (east)
  //  float targetDirectionError = 20.0;
  while (deviation > magnetometer_deviation_threshold) {
    // Get magnetic heading angle in degrees
    heading_degrees = getMagneticHeading();

    // Check if the car is not facing towards the target direction
    // heading_degrees = fmod(heading_degrees, 360.0);
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
      int duration = map(deviation, 0, 180, 15, 500); // map(deviation, 0, 180, 200, 2000)
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


void setup() {
// put your setup code here, to run once:
  pinMode(motor_lA,OUTPUT);   //left motors forward
  pinMode(motor_lB,OUTPUT);   //left motors reverse
  pinMode(motor_enable_left, OUTPUT);   // optional

  pinMode(motor_rA,OUTPUT);   //right motors forward
  pinMode(motor_rB,OUTPUT);   //rignt motors reverse
  pinMode(motor_enable_right, OUTPUT);   // optional

  pinMode(trigger_front,OUTPUT);
  pinMode(echo_front,INPUT);

  pinMode(trigger_left,OUTPUT);
  pinMode(echo_left,INPUT);

  pinMode(trigger_right,OUTPUT);
  pinMode(echo_right,INPUT);
  
  //Controlling speed (0   = off and 255 = max speed):
  analogWrite(motor_enable_left, 200);  // 90
  analogWrite(motor_enable_right, 225);  // 100

  // Unflatten the Q-table in Arduino
  int index = 0;
  for (int state = 0; state < num_states; ++state) {
    for (int action = 0; action < num_actions; ++action) {
      q_table[state][action] = flattened_q_table[index++];
    }
  }
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
  calibrateMagnetometer();  // Calibrate the magnetometer
 // ==========================================

  Serial.begin(9600);  // Initialize serial communication
}

void loop() {
//  forward(1000, 1);return;
  
  long duration_front, distance_front, duration_left, distance_left, duration_right, distance_right;

  int path_right;    // 0 indicate there is path towards right (>=10cm right from current position) || 1 indicate there is obstacle
  int path_left;     // 0 indicate there is path towards left (>=10cm left from current position)
  int path_front;  // 0 indicate there is path towards front (>=35cm forward from current position)

//  //Calculating distance
//  digitalWrite(trigger_front, LOW);
//  delayMicroseconds(2);
//  digitalWrite(trigger_front, HIGH);
//  delayMicroseconds(10);
//  digitalWrite(trigger_front, LOW);
//  duration_front = pulseIn(echo_front, HIGH);
//  distance_front= duration_front*0.034/2;
distance_left = measurePreciseDistance(trigger_left, echo_left);
distance_front = measurePreciseDistance(trigger_right, echo_right);
distance_front = measurePreciseDistance(trigger_front, echo_front);

  digitalWrite(trigger_left, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger_left, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger_left, LOW);
  duration_left = pulseIn(echo_left, HIGH);
  distance_left= duration_left*0.034/2;

  digitalWrite(trigger_right, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger_right, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger_right, LOW);
  duration_right = pulseIn(echo_right, HIGH);
  distance_right= duration_right*0.034/2;

  if (distance_left >= left_threshold) {//10
    path_left = 0;
  } else {
    path_left = 1;
  }

  if (distance_right >= right_threshold) {//10
    path_right = 0;
  } else {
    path_right = 1;
  }

  if (distance_front >= front_threshold) {//35
    path_front = 0;
  } else {
    path_front = 1;
  }
  // ==================================
  // Check if goal is reached
  // ==================================
  if ((path_left==1) && (path_right==1) && (path_front==1)){
    Serial.print("============================");Serial.print("============= Reached Goal ========");Serial.println("============================");
    Stop();
    delay(180000);  // Goal reached :: Sleep For 30 minutes

  }
  float heading_degrees = getMagneticHeading();
  Serial.println("Heading: ");Serial.print(heading_degrees);
  Serial.print("Left = ");
  Serial.print(path_left);
  Serial.print("=>");
  Serial.print(distance_left);
  Serial.println(" cm");
  Serial.print("Right = ");
  Serial.print(path_right);
  Serial.print("=>");
  Serial.print(distance_right);
  Serial.println(" cm");
  Serial.print("front = ");
  Serial.print(path_front);
  Serial.print("=>");
  Serial.print(distance_front);
  Serial.println(" cm");
  delay(50);  // pause 50 milli second

  // Print some values from the Q-table for demonstration purposes
//  Serial.println("Q-table values:");
//
//  for (int state = 0; state < num_states; ++state) {
//    for (int action = 0; action < num_actions; ++action) {
//      Serial.print("State: ");
//      Serial.print(state);
//      Serial.print(", Action: ");
//      Serial.print(action);
//      Serial.print(", Q-value: ");
//      Serial.println(q_table[state][action], 4);  // Print with 4 decimal places
//    }
//  }
//
//  delay(5000);  // Delay for 5 seconds before printing again

//  // Example binary inputs
//  int binaryInput1 = 1;
//  int binaryInput2 = 0;
//  int binaryInput3 = 1;
//  Serial.print("Path Left: ");
//  Serial.println(path_left);
//  Serial.print("Path Right: ");
//  Serial.println(path_right);
//  Serial.print("Path Front: ");
//  Serial.println(path_front);
  // Convert binary to decimal
  int decimalValue = binaryToDecimal(path_left, path_right, path_front);

  // Get Q-values for the given state
  float q_values[num_actions];
  // Replace this with your actual Q-table lookup code
  // Assuming you have the row for the given state (decimalValue) in the Q-table
//  Serial.println("Q-values:");
  for (int action = 0; action < num_actions; ++action) {
    q_values[action] = q_table[decimalValue][action];
//    Serial.println(q_table[decimalValue][action]);
  }
//  Serial.println("Thats it.");

  // Find the action with the maximum Q-value
  int maxAction = findMaxAction(q_values, num_actions);


  // Print the result
//  Serial.print("State: ");
  Serial.print(decimalValue);
  Serial.print(" -> Max Action: ");
  Serial.println(maxAction);
  // heading_degrees = getMagneticHeading();
  Serial.println("Heading: ");Serial.print(heading_degrees);

//  delay(1000);  // Delay for 15 seconds before printing again

  // Invoke functions based on the max action
  switch (maxAction) {
    case 0:
      Serial.print("---------------------");Serial.print("Decision: Left");Serial.println("---------------------");
      if (use_magnetometer_for_turning == 1){
        turn_using_magnetometer(0, 1);  //actions: [0, 1, 2] are ["left", right, forward respectively]
      } else {
                left();
        //      turnLeft();
        }
      break;
    case 1:
      Serial.print("---------------------");Serial.print("Decision: Right.");Serial.println("---------------------");
      if (use_magnetometer_for_turning == 1){
          turn_using_magnetometer(1, 1);  //actions: [0, 1, 2] are ["left", right, forward respectively]
      } else {
         right();
        // Perform action for the second action
        // Example: turnRight();
      }
      break;
    case 2:
      Serial.print("---------------------");Serial.print("Decision: Forward.");Serial.println("---------------------");
      // move_using_compass_caliberation(2); // Forward
      forward();
      // Perform action for the third action
      // Example: moveForward();
      break;
    default:
      Serial.print("It is not supposed to be displayed.the invalid action that invoked this is: ");
      Serial.println(maxAction);
      // Handle unexpected action
      break;

  }
}


long measurePreciseDistance(int trigPin, int echoPin) {
  long totalDistance = 0;

  for (int i = 0; i < numMeasurements; ++i) {
    totalDistance += measureSingleDistance(trigPin, echoPin);
    delay(50);  // Delay between measurements
  }

  // Calculate and return the average distance
  return totalDistance / numMeasurements;
}

long measureSingleDistance(int trigPin, int echoPin) {
  // Measure distance using ultrasonic sensor for a single reading
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  return pulseIn(echoPin, HIGH) * 0.034 / 2;
}