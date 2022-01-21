#include <PRIZM.h>     // include PRIZM library
PRIZM prizm;           // instantiate a PRIZM object “prizm” so we can use its functions

#define STANDARD_DELAY 100

void moveMotors(int motorDelay, int motorLeft, int motorRight); // Move both motors at once for specified amount of time: <time> <left motor power> <right motor power>
void goForward(); // Basic drive forward
void turnRight(); // Basic turn right

void movementShowcase();      // Do some basic movement to check if motors work
void rectangleDrive();        // Drive in a rectangle
void driveToWall();           // Drive to a wall/obstacle and stop
void driveToLine();           // Drive to a line and stop
void driveOnLine();           // Drive on a line 
void combo_AvoidObstacles();  // Use both the line sensor and ultrasonic sensor to avoid objects

void setup() {
  prizm.PrizmBegin();            // initialize PRIZM
  prizm.setMotorInvert(2,1);     // invert the 2nd motor so the bot drives straight
  Serial.begin(9600);            // configure the serial monitor for 9600 baud rate
  
}

void loop() {
  combo_AvoidLine();
  
}

void moveMotors(int motorDelay, int motorLeft, int motorRight) {
  prizm.setMotorPowers(motorLeft, motorRight);  // Start moving motors
  delay(motorDelay);                            // Wait specified amount of time

}

void goForward() {
  moveMotors(1000, 50, 50);   // Move both motors forward for 1s
  moveMotors(100, 125, 125);  // Break for 100ms
  delay(STANDARD_DELAY);      // Wait for the standard delay

}

void turnRight() {
  moveMotors(600, -100, 100);   // Turn right for 600ms
  moveMotors(100, 125, 125);    // Break for 100ms
  delay(STANDARD_DELAY);        // Wait for the standard delay
  
}

void movementShowcase() {
  moveMotors(3000, 100, 100);   // Move straight forward for 3 seconds
  moveMotors(3000, -100, -100); // Move straight backward for 3 seconds

  moveMotors(3000, 100, -100);  // Turn right for 3 second
  moveMotors(3000, -100, 100);  // Turn left for 3 second

  moveMotors(3000, 100, 25);    // Drive in a circle for 3 seconds
  moveMotors(3000, 25, 100);    // Drive in a circle (in reverse) for 3 seconds
  
  prizm.PrizmEnd(); // Stop driving
  
}

void rectangleDrive() {
  for(int i = 0; i < 4; i++) {  // Loop while i is less than 4, increment i each time it loops
    if(i % 2 == 0) {                // If the remainder of i / 2 equals 0: (If i is an even number)
      goForward();                      // Move forward
    }
    
    goForward();                    // Move forward
    turnRight();                    // Turn right
    }
    
  prizm.PrizmEnd();             // Stop driving
  
}

void driveToWall() {
  int distance = prizm.readSonicSensorCM(4);  // Read the sensor in centimeters
  
  if(distance > 5) {                          // If the bot's distance to a wall is greater than 5cm:
      moveMotors(300, 50, 50);                    // Move both motors forward for 300ms at half speed
      
      Serial.print(distance);                     // Print the distance the ultrasonic sensor reads
      Serial.println(" cm to wall");              // Flavor the previous text and end the line
      
    } else {                                  // Otherwise:
      Serial.println("At wall");                  // Print "At wall" to the console
      moveMotors(1000, -100, -100);               // Move both motors backward for 1s at full speed
      moveMotors(1000, -100, 100);                // Turn left for 1 second at full speed
      
      prizm.PrizmEnd();                           // Stop driving
      
  }
  
}

void driveToLine() {
  if(prizm.readLineSensor(3) == HIGH) {   // If the line sensor detects a line:
      prizm.setRedLED(HIGH);                  // Turn on the red LED
      moveMotors(50, 125, 125);               // Break for 50ms
      moveMotors(1000, 100, -100);            // Turn left for 1s
      
      prizm.PrizmEnd();                       // Stop driving
      
    } else {                              // Otherwise:
      prizm.setRedLED(LOW);                   // Turn off the red LED
      moveMotors(50, 100, 100);               // Drive forward for 50ms
  }

  delay(50);                              // Wait for 50m
  
}

void driveOnLine() {
  if(prizm.readLineSensor(3) == HIGH) { // If the line is detected:
      moveMotors(10, 25, 25);               // Move both motors forward
    } else {                            // Otherwise:
      moveMotors(10, 25, -25);              // Turn right  
  }
  
}

void combo_AvoidLine() {
  if(prizm.readSonicSensorCM(4) > 15 && prizm.readLineSensor(3) != HIGH) {   // If the ultrasonic sensor reads 15cm, or the line sensor doesn't see a line:
      moveMotors(50, 100, 100);                                                   // Move forward for 50ms
      Serial.print(prizm.readSonicSensorCM(4));                                   // Print the distance to the console
      Serial.println("cm to wall");                                               // Flavor the previous print and end the line
      
    } else {                                                                  // Otherwise:
      moveMotors(500, -125, -125);                                                // Break for 500ms
      Serial.println("Avoiding obstacle");                                        // Send message to the console
      moveMotors(1000, 100, -100);                                                // Spin around for 1s
      moveMotors(100, 50, -50);                                                   // Turn right for 100ms
  }
  
}
