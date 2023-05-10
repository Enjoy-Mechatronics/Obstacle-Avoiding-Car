#include <AFMotor.h>        // include the motor shield library. You must install this library
#include <Servo.h>          //Servo motor library. This is standard library
#include <NewPing.h>        //Ultrasonic sensor function library. You must install this library

// create motor objects
AF_DCMotor leftMotor(1, MOTOR12_64KHZ);  
AF_DCMotor rightMotor(2, MOTOR12_64KHZ);
AF_DCMotor rearLeftMotor(3, MOTOR34_64KHZ);
AF_DCMotor rearRightMotor(4, MOTOR34_64KHZ);

//sensor pins
#define trig_pin A0 //analog input 1
#define echo_pin A1 //analog input 2

#define maximum_distance 200
boolean goesForward = false;
int distance = 100;

NewPing sonar(trig_pin, echo_pin, maximum_distance); //sensor function
Servo servo_motor; //our servo name


void setup(){
  servo_motor.attach(10); //our servo pin

  servo_motor.write(90);
  delay(2000);

  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
}

void loop(){

  int distanceRight = 0;
  int distanceLeft = 0;
  delay(50);

  if (distance <= 20){
    moveStop();
    delay(300);
    moveBackward();
    delay(400);
    moveStop();
    delay(300);
    distanceRight = lookRight();
    delay(300);
    distanceLeft = lookLeft();
    delay(300);

    if (distance >= distanceLeft){
      turnRight();
      moveStop();
    }
    else{
      turnLeft();
      moveStop();
    }
  }
  else{
    moveForward(); 
  }
    distance = readPing();
}

int lookRight(){  
  servo_motor.write(10);
  delay(500);
  int distance = readPing();
  delay(100);
  servo_motor.write(90);
  return distance;
}

int lookLeft(){
  servo_motor.write(170);
  delay(500);
  int distance = readPing();
  delay(100);
  servo_motor.write(90);
  return distance;
  delay(100);
}

int readPing(){
  delay(70);
  int cm = sonar.ping_cm();
  if (cm==0){
    cm=250;
  }
  return cm;
}

void moveStop(){
  leftMotor.run(RELEASE);
  rightMotor.run(RELEASE);
  rearLeftMotor.run(RELEASE);
  rearRightMotor.run(RELEASE);
}

void moveForward(){
  if (!goesForward) {
    goesForward = true;

    leftMotor.setSpeed(150);  // set motor speed
    rightMotor.setSpeed(150);
    rearLeftMotor.setSpeed(150);
    rearRightMotor.setSpeed(150);

    leftMotor.run(FORWARD);  // run motors forward
    rightMotor.run(FORWARD);
    rearLeftMotor.run(FORWARD);
    rearRightMotor.run(FORWARD);
  }
}

void moveBackward(){
  goesForward = false;

  leftMotor.setSpeed(150);  // set motor speed
  rightMotor.setSpeed(150);
  rearLeftMotor.setSpeed(150);
  rearRightMotor.setSpeed(150);

  leftMotor.run(BACKWARD);  // run motors backward
  rightMotor.run(BACKWARD);
  rearLeftMotor.run(BACKWARD);
  rearRightMotor.run(BACKWARD);
  
}
void turnRight(){
  leftMotor.setSpeed(150); 
  rightMotor.setSpeed(150); 
  rearLeftMotor.setSpeed(150); 
  rearRightMotor.setSpeed(150); 

  leftMotor.run(FORWARD); 
  rightMotor.run(BACKWARD); 
  rearLeftMotor.run(FORWARD); 
  rearRightMotor.run(BACKWARD); 

  delay(500);

  leftMotor.setSpeed(150); 
  rightMotor.setSpeed(150); 
  rearLeftMotor.setSpeed(150); 
  rearRightMotor.setSpeed(150); 

  leftMotor.run(FORWARD); 
  rightMotor.run(FORWARD); 
  rearLeftMotor.run(FORWARD); 
  rearRightMotor.run(FORWARD);
}

void turnLeft(){
  leftMotor.setSpeed(150); 
  rightMotor.setSpeed(150); 
  rearLeftMotor.setSpeed(150); 
  rearRightMotor.setSpeed(150); 

  leftMotor.run(BACKWARD); 
  rightMotor.run(FORWARD); 
  rearLeftMotor.run(BACKWARD); 
  rearRightMotor.run(FORWARD); 

  delay(500);

  leftMotor.setSpeed(150); 
  rightMotor.setSpeed(150); 
  rearLeftMotor.setSpeed(150); 
  rearRightMotor.setSpeed(150); 

  leftMotor.run(FORWARD); 
  rightMotor.run(FORWARD); 
  rearLeftMotor.run(FORWARD); 
  rearRightMotor.run(FORWARD); 
}
