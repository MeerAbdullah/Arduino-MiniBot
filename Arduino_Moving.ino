#include <Servo.h> 

//Servo setup
Servo left; //Declare your servos
Servo right;

int leftForward = 190; //Set up some values (specific for each motor)
int leftBackward = 10;
int leftStop = 107;

int rightForward = 10;
int rightBackward = 190;
int rightStop = 108;

//Ultrasonic setup
const int trigPin = 3; //Declare ultrasonic sensor variables
const int echoPin = 2;
float duration, distance;

//Running average setup
const int numReadings = 5; 
float readings[numReadings];
int readIndex = 0;
float total = 0;
float average = 0;

void setup() {
  //Attach servo motors to respective pins
  left.attach(5);
  right.attach(6);
  
  //Set ultrasonic pins as output and input
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  
  //Fill array for running average with starting value of zero
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
  
  //Start serial monitor
  Serial.begin(9600); 
}

void loop() {
  digitalWrite(trigPin, LOW); //Reset ultrasonic sensor
  delayMicroseconds(2); 
  digitalWrite(trigPin, HIGH); //Send out ultrasonic sound wave
  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW);
  A
  
  duration = pulseIn(echoPin, HIGH); //Get pulse length
  distance = duration * 0.034 / 2; //Convert pulse length to distance
  
  if (average < 10) { //If the robot is close to something, turn one motor off and spin the other backwards (turn)
    left.write(leftBackward);
    right.write(rightStop);
  } else { //Otherwise go forward
    left.write(leftForward);
    right.write(rightForward);
  }

  total = total - readings[readIndex]; //Set running average values and calculate
  readings[readIndex] = distance;
  total = total + readings[readIndex];
  readIndex = readIndex + 1;
  if (readIndex >= numReadings) {
    readIndex = 0;
  }
  average = total / numReadings;
  delay(100); 
}
