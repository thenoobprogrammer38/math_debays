#include <Servo.h>

Servo myservo;
int potpin = 0;
int val;

const int trigPin = 9;
const int echoPin = 10;
long duration;
float distance;

unsigned long previousMillis = 0;    // Variable to store the previous timestamp
const unsigned long ultrasonicInterval = 1000;   // Interval of 1 second for ultrasonic sensor

void setup() {
  myservo.attach(3);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  val = analogRead(potpin);
  val = map(val, 0, 1023, 0, 180);
  myservo.write(val);
  delay(15);
  

  unsigned long currentMillis = millis();   // Get the current timestamp

  if (currentMillis - previousMillis >= ultrasonicInterval) {
    previousMillis = currentMillis;    // Update the previous timestamp
    
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    duration = pulseIn(echoPin, HIGH);
    distance = duration * 0.034 / 2;
    
    Serial.println ("Angle: " + String(val) + " - Distance: " + String(distance, 3));
  }

  // Rest of the code continues without delay
}
