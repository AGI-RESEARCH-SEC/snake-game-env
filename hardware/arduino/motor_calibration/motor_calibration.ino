int motor_lA = 8;
int motor_lB = 9;
int motor_enableA = 10;

int motor_rA = 3;
int motor_rB = 4;
int motor_enableB = 5;

void setup() {
  pinMode(motor_lA, OUTPUT);   // left motors forward
  pinMode(motor_lB, OUTPUT);   // left motors reverse
  pinMode(motor_enableA, OUTPUT);   // optional

  pinMode(motor_rA, OUTPUT);   // right motors forward
  pinMode(motor_rB, OUTPUT);   // right motors reverse
  pinMode(motor_enableB, OUTPUT);   // optional

  Serial.begin(9600);  // Initialize serial communication
}

void loop() {
  delay(5000);
  
  //(Optional)
  analogWrite(motor_enableA, 90);
  analogWrite(motor_enableB, 100);
  
    // Move left for 3 seconds
  left();
  delay(5000);  // Sleep for 5 seconds

  // Move right for 3 seconds
  right();
  delay(5000);  // Sleep for 5 seconds
  
  // Move forward for 3 seconds
  forward();
  delay(5000);  // Sleep for 5 seconds
  
  // Move back for 3 seconds
  back();
  delay(5000);  // Sleep for 5 seconds


  delay(7000);

  
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
  delay(1950);
  Stop();
}

void Stop() {
  digitalWrite(motor_lA, LOW);
  digitalWrite(motor_lB, LOW);
  digitalWrite(motor_rA, LOW);
  digitalWrite(motor_rB, LOW);
  delay(300);
}
