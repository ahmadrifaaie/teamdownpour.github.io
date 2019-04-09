const int swPin=2; //slideswitch control pin
const int rainSensorPin=A5; //analog control pin
const int servoPin=9; //servo control pin
int sw;//switch state
int rain; //rain state (analog)
int servoState = 0;    // window open

#include <Servo.h>

Servo servo;

void closewindow()
{
  servo.write(90);
  delay(2000);
}

void openwindow()
{
  servo.write(0);// open window
  delay(2000);
}

void setup()
{
  pinMode(swPin,INPUT_PULLUP);
  servo.attach(servoPin);
  servo.write(0);
  delay(2000);
  Serial.begin(9600);
}

void loop()
{
  sw=digitalRead(swPin);//detect slideswitch
  if (sw==LOW) //if user decides to close windows
  {
    if (servoState==0)
    {
      closewindow();
      servoState = 1;
    }
  }
  else // sw is LOW
  {
    rain=analogRead(rainSensorPin);
    Serial.println(rain);
    delay(500);
    if(rain<500)
    {
      if(servoState==0)
      {
        closewindow();
        servoState=1;
      }
    }
    else
    {
      if (servoState==1)
      {
        openwindow();
        servoState=0;
      }
    }
  }
}
