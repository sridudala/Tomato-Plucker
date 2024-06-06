#include <Servo.h> // Include Servo library for plucker movement

// Define motor control pins (modify based on your motor driver)
#define MOTOR_A_1 5
#define MOTOR_A_2 4
#define MOTOR_B_1 3
#define MOTOR_B_2 2

// Define servo pin for plucker
#define PLUCKER_SERVO 9

// Create servo object
Servo pluckerServo;

// Define color detection constants (adjust based on your color sensor)
#define RED_THRESHOLD_LOW 100  // Minimum red value for ripe tomato
#define RED_THRESHOLD_HIGH 200 // Maximum red value for ripe tomato

// Function to move the robot forward
void moveForward(int speed) {
  digitalWrite(MOTOR_A_1, HIGH);
  digitalWrite(MOTOR_A_2, LOW);
  digitalWrite(MOTOR_B_1, HIGH);
  digitalWrite(MOTOR_B_2, LOW);
  analogWrite(MOTOR_A_1, speed);
  analogWrite(MOTOR_B_1, speed);
}

// Function to move the robot backward
void moveBackward(int speed) {
  digitalWrite(MOTOR_A_1, LOW);
  digitalWrite(MOTOR_A_2, HIGH);
  digitalWrite(MOTOR_B_1, LOW);
  digitalWrite(MOTOR_B_2, HIGH);
  analogWrite(MOTOR_A_2, speed);
  analogWrite(MOTOR_B_2, speed);
}

// Function to rotate the robot left
void rotateLeft(int speed) {
  digitalWrite(MOTOR_A_1, LOW);
  digitalWrite(MOTOR_A_2, HIGH);
  digitalWrite(MOTOR_B_1, HIGH);
  digitalWrite(MOTOR_B_2, LOW);
  analogWrite(MOTOR_A_2, speed);
  analogWrite(MOTOR_B_1, speed);
}

// Function to rotate the robot right
void rotateRight(int speed) {
  digitalWrite(MOTOR_A_1, HIGH);
  digitalWrite(MOTOR_A_2, LOW);
  digitalWrite(MOTOR_B_1, LOW);
  digitalWrite(MOTOR_B_2, HIGH);
  analogWrite(MOTOR_A_1, speed);
  analogWrite(MOTOR_B_2, speed);
}

// Function to stop the robot
void stopRobot() {
  digitalWrite(MOTOR_A_1, LOW);
  digitalWrite(MOTOR_A_2, LOW);
  digitalWrite(MOTOR_B_1, LOW);
  digitalWrite(MOTOR_B_2, LOW);
}

// Function to pluck a tomato
void pluckTomato() {
  pluckerServo.write(180); // Move servo to pluck position
  delay(1000);             // Hold for plucking duration
  pluckerServo.write(0);    // Move servo back to starting position
}

// Function to read color sensor and detect ripe tomato
int readColor() {
  int redValue = analogRead(COLOR_SENSOR_PIN); // Replace with your color sensor pin
  if (redValue >= RED_THRESHOLD_LOW && redValue <= RED_THRESHOLD_HIGH) {
    return 1; // Ripe tomato detected
  } else {
    return 0; // Not a ripe tomato
  }
}

void setup() {
  Serial.begin(9600);  // Initialize serial communication for debugging

  // Set motor control pins as outputs
  pinMode(MOTOR_A_1, OUTPUT);
  pinMode(MOTOR_A_2, OUTPUT);
  pinMode(MOTOR_B_1, OUTPUT);
  pinMode(MOTOR_B_2, OUTPUT);

  // Attach servo to pin
  pluckerServo.attach(PLUCKER_SERVO);

  // Set color sensor pin as input (replace with your color sensor pin setup)
  pinMode(COLOR_SENSOR_PIN, INPUT); // Replace with your color sensor pin
}

void loop() {
  int colorValue = readColor();

  if (colorValue == 1) { // Ripe tomato detected
    stopRobot();
    pluckTomato();
    // (Optional) Add logic for moving robot away from plucked tomato or signaling for collection
  } else {
    moveForward(100); // Replace 100 with desired speed (