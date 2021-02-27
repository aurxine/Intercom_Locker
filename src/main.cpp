#include <Arduino.h>
#include<Servo.h>

Servo locker; // this servo locks the hook of the key holder
#define Servo_Pin 9
#define Initial_Position 90
#define Lock_Angle 90
#define Unlock_Angle 0

#define LDR_Pin A0
float LDR_Threshold = 500;

#define Unlock_Pin 2
bool isLocked = true;

void Turn_Angle(Servo &servo, int angle)
{
  int current_angle = servo.read();
  int difference_of_angles = angle - current_angle;

  for(int i = 0; i < abs(difference_of_angles); i++)
  {
    current_angle += difference_of_angles / abs(difference_of_angles);
    Serial.print("Current angle: ");
    Serial.println(current_angle);
    servo.write(current_angle);
    delay(50);
  }
}

void Unlock()
{
  isLocked = false;
}

void setup() 
{
  Serial.begin(9600);
  // pinMode(8, OUTPUT);
  // pinMode(7, OUTPUT);
  // digitalWrite(8, HIGH);
  // digitalWrite(7, LOW);
  pinMode(Unlock_Pin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(Unlock_Pin), Unlock, FALLING);

  locker.attach(Servo_Pin);

  locker.write(Initial_Position);

  // delay(2000);

  // locker.write(30);

  // delay(2000);

  // Turn_Angle(locker, 50);

  // delay(1000);

  // Turn_Angle(locker, 100);

  // delay(1000);

  // Turn_Angle(locker, 30);

  
}

void loop() 
{
  if(!isLocked)
  {
    Turn_Angle(locker, Unlock_Angle);
  } 

  if(analogRead(LDR_Pin) > LDR_Threshold)
  {
    Turn_Angle(locker, Lock_Angle);
    isLocked = true;
  }

  else
  {
    isLocked = false;
  }
}