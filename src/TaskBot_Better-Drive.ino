#include <PRIZM.h>     // include PRIZM library
PRIZM prizm;           // instantiate a PRIZM object “prizm” so we can use its functions

#define STANDARD_DELAY 100

void moveMotors(int motorDelay, int motorLeft, int motorRight);
void goForward();
void turnRight();

void movementShowcase();
void rectangleDrive();
void driveToWall();
void driveToLine();
void maze_challange(); 

void setup() {
  prizm.PrizmBegin();            // initialize PRIZM
  prizm.setMotorInvert(2,1);     // invert the 2nd motor so the bot drives straight
  Serial.begin(9600);            // configure the serial monitor for 9600 baud rate
  
}

void loop() {
  maze_challange();
  
}

void moveMotors(int motorDelay, int motorLeft, int motorRight) {
  prizm.setMotorPowers(motorLeft, motorRight);  // Start moving motors
  delay(motorDelay);                            // Wait specified amount of time

}

void goForward() {
  moveMotors(1000, 50, 50);
  moveMotors(100, 125, 125);
  delay(STANDARD_DELAY);

}

void turnRight() {
  moveMotors(600, -100, 100);
  moveMotors(100, 125, 125);
  delay(STANDARD_DELAY);
  
}

void movementShowcase() {
  moveMotors(3000, 100, 100);   // Move straight forward for 3 seconds
  moveMotors(3000, -100, -100); // Move straight backward for 3 seconds

  moveMotors(3000, 100, -100);  // Turn right for 3 second
  moveMotors(3000, -100, 100);  // Turn left for 3 second

  moveMotors(3000, 100, 25);    // Drive in a circle for 3 seconds
  moveMotors(3000, 25, 100);  // Drive in a circle (in reverse) for 3 seconds
  
  prizm.PrizmEnd(); // Stop driving
  
}

void rectangleDrive() {
  for(int i = 0; i < 4; i++) {
    if(i % 2 == 0) {  // If the remainder of i / 2 equals 0
      goForward();
    }
    
    goForward();
    turnRight();
    }
    
  prizm.PrizmEnd();
  
}

void driveToWall() {
  int distance = prizm.readSonicSensorCM(4);  // Read the sensor in centimeters
  
  if(distance > 5) {            // If the bot's distance to a wall is greater than 5cm:
      moveMotors(300, 50, 50);
      
      Serial.print(distance);
      Serial.println(" cm to wall");
      
    } else {                    // Otherwise:
      Serial.println("At wall");
      moveMotors(1000, -100, -100);
      moveMotors(1000, -100, 100);
      
      prizm.PrizmEnd();
      
  }
  
}

void driveToLine() {
  if(prizm.readLineSensor(3) == HIGH) {
      prizm.setRedLED(HIGH);
      moveMotors(50, 125, 125);
      moveMotors(1000, 100, -100);
      
      prizm.PrizmEnd();
      
    } else {
      prizm.setRedLED(LOW);
      moveMotors(50, 100, 100);
  }

  delay(50);
  
}

void maze_challange() {
    moveMotors(2000, 25, 25);   // Drive forward
    moveMotors(1600, -25, 25);  // Turn right
    moveMotors(2000, 25, 25);   // Drive forward
    //moveMotors(50, -25, 25);    // Turn right
    moveMotors(3000, 50, 50);   // Drive forward
    moveMotors(700, 25, -25);   // Turn left
    moveMotors(3500, 50, 50);   // Drive forward
    moveMotors(700, 25, -25);   // Turn left
    moveMotors(1000, 25, 25);   // Drive forward
    /*
    moveMotors(700, 25, -25);   // Turn right
    moveMotors(1500, 50, 50);   // Drive forward
    moveMotors(1000, -25, 25);   // Turn Right
    moveMotors(1000, 25, 25);    // Drive forward
    moveMotors(900, 25, -25);   // Turn left
    moveMotors(700, 25, 25);    // Drive forward
    */
    
  prizm.PrizmEnd();
}
