const int numMeasurements = 5;  // Number of ultrasonic sensor measurements to average
int left_threshold = 35;
int right_threshold = 35;
int front_threshold = 30;

int motor_lA = 8;
int motor_lB = 9;
int motor_enableA = 10;

int motor_rA = 3;
int motor_rB = 4;
int motor_enableB = 5;

int trigger_left = A0;
int echo_left = A1;

int trigger_right = A2;
int echo_right = A3;

int trigger_front = A4;
int echo_front = A5;

// Define the flattened Q-table copied from Python
float flattened_q_table[] = {-0.14567542786524684, 0.028992119894766844, -0.2658059392757915, 15.500593710459835, -0.15679, -0.5751383360655641, -0.5, -0.7610600150158306, 19.256544264254092, 16.330889837828664, -2.594840781380889, -2.474224227054556, -0.852180077055561, -0.7006457235470309, 12.950534339413846, -2.2842125693118476, -2.776785077874974, -2.6859971955040907, -1.6150456834794744, -1.8485000844551536, 12.096579828480882, -2.7116605133971876, -3.133167873327339, -3.182911142097555};

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

  Serial.begin(9600);  // Initialize serial communication
}

void loop() {
  long duration_front, distance_front, duration_left, distance_left, duration_right, distance_right;

  int path_right;    // 0 indicate there is path towards right (>=10cm right from current position) || 1 indicate there is obstacle
  int path_left;     // 0 indicate there is path towards left (>=10cm left from current position)
  int path_front;  // 0 indicate there is path towards front (>=35cm forward from current position)

  //Controlling speed (0   = off and 255 = max speed):     
  //(Optional)
  analogWrite(motor_enableA, 90);
  analogWrite(motor_enableB, 100);
  
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
      left();
      //      turnLeft();
      break;
    case 1:
      Serial.println("Decision: Right.");
      right();
      // Perform action for the second action
      // Example: turnRight();
      break;
    case 2:
      Serial.println("Forward");
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


void right() {
  digitalWrite(motor_lA, HIGH);
  digitalWrite(motor_lB, LOW);
  digitalWrite(motor_rA, HIGH);
  digitalWrite(motor_rB, LOW);
  delay(1900);
  Stop();
}

void forward() {
  digitalWrite(motor_lA, HIGH);
  digitalWrite(motor_lB, LOW);
  digitalWrite(motor_rA, LOW);
  digitalWrite(motor_rB, HIGH);
  delay(1500);
  Stop();
}

void back() {
  digitalWrite(motor_lA, LOW);
  digitalWrite(motor_lB, HIGH);
  digitalWrite(motor_rA, HIGH);
  digitalWrite(motor_rB, LOW);
  delay(3000);
  Stop();
}

void left() {
  digitalWrite(motor_lA, LOW);
  digitalWrite(motor_lB, HIGH);
  digitalWrite(motor_rA, LOW);
  digitalWrite(motor_rB, HIGH);
  delay(1750);
  Stop();
}

void Stop() {
  digitalWrite(motor_lA, LOW);
  digitalWrite(motor_lB, LOW);
  digitalWrite(motor_rA, LOW);
  digitalWrite(motor_rB, LOW);
  delay(300);
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
