#include <Joystick.h>

int RXLED = 17;
int pin = 9;

void setup()
{
  // put your setup code here, to run once:
  pinMode(pin, INPUT_PULLUP);
  Joystick.begin();
}

void loop()
{
  // put your main code here, to run repeatedly:
  int currState = digitalRead(pin); 
  if(currState)
  {
    digitalWrite(RXLED, HIGH);
    Joystick.setButton(0, !currState);
  }
  else
  {
    digitalWrite(RXLED, LOW);
    Joystick.setButton(0, !currState);
  }
  delay(100);
}
