#include <AFMotor.h>
#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include <Dabble.h>


int MAX_SPEED = 150; //Max speed the wheels can move while moving forward and backward.
int turnSpeed = 120; // Max speed the wheels can move when turning.
int speedSet = 0; // Variable used in for loops later on where we will will gradually increase the motor speed.
bool atSpeed = false; // Used to figure out if the car is moving already or not, so we don't run our motor acceleration code.
int accelerationIncrement = 10; //How much we increment the accelleration of our motors by, higher = higher acceleration, but will drain the battery.
char command; //This var is used to store the command we receive from the Bluetooth connection.


//Motor Declarations using the AF_DCMotor Library
AF_DCMotor motor1(1, MOTOR12_1KHZ); //BACK LEFT
AF_DCMotor motor2(2, MOTOR12_1KHZ); // BACK RIGHT
AF_DCMotor motor3(3, MOTOR34_1KHZ); // FRONT LEFT
AF_DCMotor motor4(4, MOTOR34_1KHZ); //FRONT RIGHT

void setup() {
  // WITH BLUETOOTH
  Serial.begin(250000); //Set up Serial and Dabble for Bluetooth connection
  Dabble.begin(9600, 9, 10); //Initialize RX & TX pins as 9 and 10 and begin Dabble communication
  motorStop(); // Initialize the motors to stop until we recive a command
}

void loop() {
  Dabble.processInput();//this function is used to refresh data obtained from Bluetooth connection, calling this function is mandatory in order to get data properly
  //Main function below, we want to check if any buttons are pressed, if not we will stop the motors
  if(GamePad.isUpPressed() || GamePad.isDownPressed() || GamePad.isLeftPressed() || GamePad.isRightPressed()){
  if (GamePad.isUpPressed())
  {
    motorForward(); // If up is pressed, move motors forward
  }

  if (GamePad.isDownPressed())
  {
    motorBackward(); // If back is pressed, move motors backward
  }

  if (GamePad.isLeftPressed())
  {
    motorLeft(); // If left is pressed, move motors left
  }

  if (GamePad.isRightPressed())
  {
    motorRight(); // If right is pressed, move motors right
  }
  }
  else{
    motorStop(); // Stop motors if no buttons are pressed
  }
}

void motorStop() {
  motor1.run(RELEASE); 
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
  atSpeed = false;
}

void motorForward(){
  if (!atSpeed) { //If we're at speed and still pushing the forward button, the motors just continue to run until they are stopped, so skip the function
    motor1.run(FORWARD);
    motor2.run(FORWARD);
    motor3.run(FORWARD);
    motor4.run(FORWARD);
    for (speedSet = 0; speedSet < MAX_SPEED; speedSet+= accelerationIncrement) { //The for loops are used to gradually increase speed to the motors in order to not drain the batteries
      int speed = map(speedSet, 0, MAX_SPEED, 0, 255);
      motor1.setSpeed(speed);
      motor2.setSpeed(speed);
      motor3.setSpeed(speed);
      motor4.setSpeed(speed);
      delay(10);
    }
    atSpeed = true;
  }
}
void motorBackward(){
  if (!atSpeed) {
    motor1.run(BACKWARD);
    motor2.run(BACKWARD);
    motor3.run(BACKWARD);
    motor4.run(BACKWARD);
    for (speedSet = 0; speedSet < MAX_SPEED; speedSet+=accelerationIncrement) {
      int speed = map(speedSet, 0, MAX_SPEED, 0, 255);
      motor1.setSpeed(speed);
      motor2.setSpeed(speed);
      motor3.setSpeed(speed);
      motor4.setSpeed(speed);
      delay(10);
    }
    atSpeed = true;
  }
}

void motorRight(){
  if (!atSpeed) {
    motor1.run(FORWARD);
    motor2.run(BACKWARD);
    motor3.run(BACKWARD);
   motor4.run(FORWARD);
    for (speedSet = 0; speedSet < turnSpeed; speedSet += accelerationIncrement) {
      int speed = map(speedSet, 0, turnSpeed, 0, 255);
      motor1.setSpeed(speed);
      motor2.setSpeed(speed);
      motor3.setSpeed(speed);
      motor4.setSpeed(speed);
      delay(10);
    }
    atSpeed = true;
  }
}

void motorLeft(){
  if (!atSpeed) {
    motor1.run(BACKWARD);
    motor2.run(FORWARD);
    motor3.run(FORWARD);
    motor4.run(BACKWARD);
    for (speedSet = 0; speedSet < turnSpeed; speedSet += accelerationIncrement) {
      int speed = map(speedSet, 0, turnSpeed, 0, 255);
      motor1.setSpeed(speed);
      motor2.setSpeed(speed);
      motor3.setSpeed(speed);
      motor4.setSpeed(speed);
      delay(10);
    }
    atSpeed = true;
  }
}
