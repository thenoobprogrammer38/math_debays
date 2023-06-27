#include "Wire.h"
#include "I2Cdev.h"
#include "MPU6050.h"

MPU6050 mpu;
int16_t ax, ay, az;
int16_t gx, gy, gz;

struct MyData {
  byte X;
  byte Y;
  byte Z;
};

MyData data;

const int FLAT_THRESHOLD = 5000;  // Threshold value for surface detection

const int ledPin = 8;  // Pin connected to the LED
const int buzzer = 7;

const int sideLaser = 6;

int status = 0;


void setup() {
  Serial.begin(9600);
  Wire.begin();
  mpu.initialize();
  pinMode(buzzer, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(sideLaser, OUTPUT);
}


//looping and getting the values
void loop() {
  digitalWrite(sideLaser, HIGH);

  //mapping the accelerometer values
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  data.X = map(ax, -8000, 8000, 0, 255);  // X axis data (reduced range)
  data.Y = map(ay, -8000, 8000, 0, 255);  // Y axis data (reduced range)
  data.Z = map(az, -8000, 8000, 0, 255);  // Z axis data (reduced range)

  if ((data.Z >= 160 && data.Z <= 175)) {

    if (status == 0) {
      status = 1;

      digitalWrite(ledPin, HIGH);
      beep();
    }

  } else {
    status = 0;

    //Blinking the LED
    digitalWrite(ledPin, LOW);
    delay(75);
    digitalWrite(ledPin, HIGH);
    delay(75);

  }
  
  Serial.print("Axis X = ");
  Serial.print(data.X);
  Serial.print("  ");
  Serial.print("Axis Y = ");
  Serial.print(data.Y);
  Serial.print("  ");
  Serial.print("Axis Z  = ");
  Serial.println(data.Z);

}

//function that makes the melody of the buzzer
void beep() {
  digitalWrite(buzzer, HIGH);
  delay(75);
  digitalWrite(buzzer, LOW);
  delay(75);
  digitalWrite(buzzer, HIGH);
  delay(75);
  digitalWrite(buzzer, LOW);

}
