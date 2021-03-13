#include <Arduino.h>
#include<Servo.h>

Servo locker; // this servo locks the hook of the key holder
#define Servo_Pin 10
#define Initial_Position 0
#define Lock_Angle 90
#define Unlock_Angle 0

#define bounce_time 200

#define Button_Pin A2
float Button_Threshold = 1020;

#define Unlock_Pin 3
bool isLocked = true;

void Turn_Angle(Servo &servo, int angle)
{
  int current_angle = servo.read();
  int difference_of_angles = angle - current_angle;

  for(int i = 0; i < abs(difference_of_angles); i += 5)
  {
    current_angle += 5*difference_of_angles / abs(difference_of_angles);
    Serial.print("Current angle: ");
    Serial.println(current_angle);
    servo.write(current_angle);
    delay(50);
  }
}

void Unlock()
{
  static unsigned long last_interrupt_time = 0;
    unsigned long interrupt_time = millis();
    // Serial.println("interrupt activated");
    if(interrupt_time - last_interrupt_time > bounce_time)
    {
        Serial.println("Unlocking Command Given");
        isLocked = false;
    }

    last_interrupt_time = interrupt_time;

}

void setup() 
{
  Serial.begin(9600);
  pinMode(Unlock_Pin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(Unlock_Pin), Unlock, FALLING);

  locker.attach(Servo_Pin);

  delay(2000);
  locker.write(Initial_Position);

}

void loop() 
{

  if(!isLocked)
  {
    Serial.println("Unlocking");
    Turn_Angle(locker, Unlock_Angle);
  } 

  Serial.println(analogRead(Button_Pin));
  
  if(analogRead(Button_Pin) >= Button_Threshold)
  {
    Serial.println("Locking");
    Turn_Angle(locker, Lock_Angle);
    isLocked = true;
  }
  delay(500);

  // else
  // {
  //   isLocked = false;
  // }
}