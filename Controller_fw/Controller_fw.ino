#include <Joystick.h>

int RXLED = 17;
int pin = 9;
static const uint8_t button_up = 2;
static const uint8_t button_down = 3;
static const uint8_t button_left = 4;
static const uint8_t button_right = 5;


static const uint8_t button_1 = A3;
static const uint8_t button_2 = A2;
static const uint8_t button_3 = A1;
static const uint8_t button_4 = A0;
static const uint8_t button_5 = 15
static const uint8_t button_6 = 14;

static const uint8_t button_big = 16;

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
