int motor_lA = 8;
int motor_lB = 9;
int motor_enableA = 10;

int motor_rA = 3;
int motor_rB = 4;
int motor_enableB = 5;

int trigger_front = A0;
int echo_front = A1;

int trigger_left = A2;
int echo_left = A3;

int trigger_right = A4;
int echo_right = A5;

// Define the flattened Q-table copied from Python
float flattened_q_table[] = {0.83628823, 0.32465725, 0.43946987, 0.92848217, 0.31976622, 0.02879293, 0.39303688, 0.86101691, 0.84169302, 0.91988256, 0.27034799, 0.20408083, 0.81865994, 0.47306999, 0.02823797, 0.40868649, 0.79734044, 0.16925595, 0.1252419,  0.93447908, 0.1162519,  0.21943516, 0.58814741, 0.66238703};

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
  analogWrite(motor_enableA, 80);
  analogWrite(motor_enableB, 80);
  
  //Calculating distance
  digitalWrite(trigger_front, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger_front, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger_front, LOW);
  duration_front = pulseIn(echo_front, HIGH);
  distance_front= duration_front*0.034/2;

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

  Serial.print("front = ");
  Serial.print(distance_front);
  Serial.println(" cm");
  Serial.print("Left = ");
  Serial.print(distance_left);
  Serial.println(" cm");
  Serial.print("Right = ");
  Serial.print(distance_right);
  Serial.println(" cm");
  delay(50);  // pause 50 milli second
  
  if (distance_left >= 10) {
    path_left = 0;
  } else {
    path_left = 1;
  }
  
  if (distance_right >= 10) {
    path_right = 0;
  } else {
    path_right = 1;
  }
  
  if (distance_front >= 35) {
    path_front = 0;
  } else {
    path_front = 1;
  }
  
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
  Serial.print("Path Left: ");
  Serial.println(path_left);
  Serial.print("Path Right: ");
  Serial.println(path_right);
  Serial.print("Path Front: ");
  Serial.println(path_front);
  // Convert binary to decimal
  int decimalValue = binaryToDecimal(path_left, path_right, path_front);

  // Get Q-values for the given state
  float q_values[num_actions];
  // Replace this with your actual Q-table lookup code
  // Assuming you have the row for the given state (decimalValue) in the Q-table
  Serial.println("Q-values:");
  for (int action = 0; action < num_actions; ++action) {
    q_values[action] = q_table[decimalValue][action];
    Serial.println(q_table[decimalValue][action]);
  }
  Serial.println("Thats it.");

  // Find the action with the maximum Q-value
  int maxAction = findMaxAction(q_values, num_actions);


  // Print the result
  Serial.print("State: ");
  Serial.print(decimalValue);
  Serial.print(" -> Max Action: ");
  Serial.println(maxAction);

  delay(15000);  // Delay for 15 seconds before printing again
  
  // Invoke functions based on the max action
  switch (maxAction) {
    case 0:
      Serial.println("This is definitely forward.");
      forward();
      //      turnLeft();
      break;
    case 1:
      Serial.println("Left. brrrrrmmmmrrr....");
      left();
      // Perform action for the second action
      // Example: turnRight();
      break;
    case 2:
      Serial.println("Right Turn, Right Turn.");
      right();
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


void forward()
{
  digitalWrite(motor_lA,HIGH);
  digitalWrite(motor_lB,LOW);
  digitalWrite(motor_rA,HIGH);
  digitalWrite(motor_rB,LOW);
  delay(1000);
}


void right(){
  digitalWrite(motor_lA,HIGH);
  digitalWrite(motor_lB,LOW);
  digitalWrite(motor_rA,LOW);
  digitalWrite(motor_rB,HIGH);
 delay(10);
}


void left(){
  digitalWrite(motor_lA,LOW);
  digitalWrite(motor_lB,HIGH);
  digitalWrite(motor_rA,HIGH);
  digitalWrite(motor_rB,LOW);
  delay(10);
}



void Stop(){
  digitalWrite(motor_lA,LOW);
  digitalWrite(motor_lB,LOW);
  digitalWrite(motor_rA,LOW);
  digitalWrite(motor_rB,LOW);
  delay(300);
}
