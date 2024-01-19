///source: https://maker.pro/arduino/projects/how-to-build-an-arduino-based-maze-solving-robot
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
//Written in loop()
//  analogWrite(motor_enableA, 80);
//  analogWrite(motor_enableB, 88);

  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  //  Serial.begin(9600);
  long duration_front, distance_front, duration_left, distance_left, duration_right, distance_right;

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

  forward();
//  if (distance_front >20){
//
//    forward();
//    
//    if(distance_left > 10&& distance_left<20){
//      forward();
//    }
//    if(distance_left >=20){
//       left();
//       delay(30);
//       forward();
//    }
//    if(distance_left<10 && distance_left>0){
//      right();
//      delay(30);
//      forward();
//    }
// } 
//  
//  if(distance_front<=20&& distance_right > 20){
//    Stop();
//    delay(1000);
//    right();
//    delay(400);
//    
//  }
//
//  if(distance_front<=20 && distance_right<20){
//    Stop();
//    delay(1000);
//    right();
//    delay(800);
//   
//  }
  
  
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


  
  
    

   
