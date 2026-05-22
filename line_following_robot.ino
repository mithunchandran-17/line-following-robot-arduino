#include <AFMotor.h>

// Motor initialization
AF_DCMotor leftMotor(1);
AF_DCMotor rightMotor(2);

// IR Sensor pins
int leftSensor = A0;
int rightSensor = A1;

// Sensor values
int leftValue = 0;
int rightValue = 0;

// Threshold (adjust after testing)
int threshold = 500;

// Base speed
int baseSpeed = 150;

// Proportional constant (tune this!)
float Kp = 0.2;

void setup() {
  Serial.begin(9600);

  pinMode(leftSensor, INPUT);
  pinMode(rightSensor, INPUT);

  Serial.println("🚗 Advanced Line Following Robot Started");
}

void loop() {

  // Read analog sensor values
  leftValue = analogRead(leftSensor);
  rightValue = analogRead(rightSensor);

  // Print values for calibration/debugging
  Serial.print("Left: ");
  Serial.print(leftValue);
  Serial.print(" | Right: ");
  Serial.println(rightValue);

  // Calculate error
  int error = leftValue - rightValue;

  // Proportional correction
  int correction = Kp * error;

  // Adjust motor speeds
  int leftSpeed = baseSpeed - correction;
  int rightSpeed = baseSpeed + correction;

  // Constrain speeds (0–255)
  leftSpeed = constrain(leftSpeed, 0, 255);
  rightSpeed = constrain(rightSpeed, 0, 255);

  // Set motor speeds
  leftMotor.setSpeed(leftSpeed);
  rightMotor.setSpeed(rightSpeed);

  // Decision logic (fallback for extreme cases)
  if (leftValue < threshold && rightValue < threshold) {
    moveForward();
  }
  else if (leftValue < threshold && rightValue > threshold) {
    turnLeftSoft();
  }
  else if (leftValue > threshold && rightValue < threshold) {
    turnRightSoft();
  }
  else {
    stopRobot();
  }

  delay(5);  // small delay for stability
}

// --------- Movement Functions ---------

void moveForward() {
  leftMotor.run(FORWARD);
  rightMotor.run(FORWARD);
}

void turnLeftSoft() {
  leftMotor.run(FORWARD);
  rightMotor.run(FORWARD);
}

void turnRightSoft() {
  leftMotor.run(FORWARD);
  rightMotor.run(FORWARD);
}

void stopRobot() {
  leftMotor.run(RELEASE);
  rightMotor.run(RELEASE);
}
