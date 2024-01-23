#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>

const int numMeasurements = 5;  // Number of ultrasonic sensor measurements to average
int left_threshold = 35;
int right_threshold = 35;
int front_threshold = 30;

int continuous_actions = 1; // 0 Represent Delay after each action; 1 Represent Discrete actions

int use_compass_caliberation = 0; // turn on/off the compass calibration. 1 is on. 2 is off. 
// float initialDirection = 70;// 100.0; // angle (degrees) the bot is facing initially.
float initialDirection = 210;// college // angle (degrees) the bot is facing initially.
float DeviationThreshold = 20.0; // angle (degrees) deviation threshold
/* Assign a unique ID to this sensor at the same time */
Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);

int motor_lA = 8;
int motor_lB = 9;
int motor_enableA = 10;

int motor_rA = 3;
int motor_rB = 4;
int motor_enableB = 5;

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

void forward(int delay_parameter = 1000) {
  Serial.println("Forward");
  digitalWrite(motor_lA, HIGH);
  digitalWrite(motor_lB, LOW);
  digitalWrite(motor_rA, LOW);
  digitalWrite(motor_rB, HIGH);
  
  if (continuous_actions != 1){
    // agent takes continuous actions
    delay(1500);
    Stop();
  }
}

void right(int delay_parameter = 1020, bool move_forward=1) {// 1200
  Serial.println("Right");
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

void left(int delay_parameter = 1000, bool move_forward=1) {// 1250
  Serial.println("Left");
  Serial.println(delay_parameter);
  digitalWrite(motor_lA, LOW);
  digitalWrite(motor_lB, HIGH);
  digitalWrite(motor_rA, LOW);
  digitalWrite(motor_rB, HIGH);
  delay(delay_parameter);
  Stop();
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
  delay(300);
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




// Function to rotate towards the target direction
void move_using_compass_caliberation(int action) {
  //actions: [0, 1, 2] represent ["left", "right", "forward"] respectively
  float target_degrees;
  float heading_degrees;
  float deviation1;
  float deviation2;
  float deviation;
  Serial.println("======================");Serial.println("Moving ");Serial.println(action);Serial.println("======================");
   if (action == 0) {
    target_degrees = initialDirection + 90;   // rotate left
    Serial.println("======================");Serial.println("Moving Left");Serial.println("======================");
  } else if (action == 1) {
    target_degrees = initialDirection - 90;   // rotate right
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
      int duration = map(deviation, 0, 180, 200, 2000);
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
// put your setup code here, to run once:
  pinMode(motor_lA,OUTPUT);   //left motors forward
  pinMode(motor_lB,OUTPUT);   //left motors reverse
  pinMode(motor_enableA, OUTPUT);   // optional

  pinMode(motor_rA,OUTPUT);   //right motors forward
  pinMode(motor_rB,OUTPUT);   //rignt motors reverse
  pinMode(motor_enableB, OUTPUT);   // optional

  pinMode(trigger_front,OUTPUT);
  pinMode(echo_front,INPUT);

  pinMode(trigger_left,OUTPUT);
  pinMode(echo_left,INPUT);

  pinMode(trigger_right,OUTPUT);
  pinMode(echo_right,INPUT);
  
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
 // ==========================================

  Serial.begin(9600);  // Initialize serial communication
}

void loop() {
  long duration_front, distance_front, duration_left, distance_left, duration_right, distance_right;

  int path_right;    // 0 indicate there is path towards right (>=10cm right from current position) || 1 indicate there is obstacle
  int path_left;     // 0 indicate there is path towards left (>=10cm left from current position)
  int path_front;  // 0 indicate there is path towards front (>=35cm forward from current position)

  //Controlling speed (0   = off and 255 = max speed):     
  //(Optional)
  analogWrite(motor_enableA, 90);  // 90
  analogWrite(motor_enableB, 100);  // 100
  
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
    delay(30000000000);  // Sleep For 3 seconds

  }
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

//  delay(1000);  // Delay for 15 seconds before printing again
  
  // Invoke functions based on the max action
  switch (maxAction) {
    case 0:
      Serial.println("Decision: Left");
      if (use_compass_caliberation == 1){
        move_using_compass_caliberation(0); // Left by magnetometer caliberation
      } else {
        left();
        //      turnLeft();
        }
      break;
    case 1:
      Serial.println("Decision: Right.");
      if (use_compass_caliberation == 1){
          move_using_compass_caliberation(1); // Right by magnetometer caliberation
      } else {
         right();
        // Perform action for the second action
        // Example: turnRight();
      }
      break;
    case 2:
      Serial.println("Forward");
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
