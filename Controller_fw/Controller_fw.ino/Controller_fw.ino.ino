#include <Gamepad.h>

//Initializing a Gamepad
Gamepad gp;


int RXLED = 17;

// Button constant definitions
static const uint8_t button_up = 2;
static const uint8_t button_down = 3;
static const uint8_t button_left = 4;
static const uint8_t button_right = 5;

static const uint8_t button_1 = A3;
static const uint8_t button_2 = A2;
static const uint8_t button_3 = A1;
static const uint8_t button_4 = A0;
static const uint8_t button_5 = 15;
static const uint8_t button_6 = 14;

static const uint8_t button_big = 16;

// Button state definitions
bool button_up_state = false;
bool button_down_state = false;
bool button_left_state = false;
bool button_right_state = false;

bool button_1_state = false;
bool button_2_state = false;
bool button_3_state = false;
bool button_4_state = false;
bool button_5_state = false;
bool button_6_state = false;

bool button_big_state = false;

// Button index definitions
uint8_t button_up_index = 0;
uint8_t button_down_index = 1;
uint8_t button_left_index = 2;
uint8_t button_right_index = 3;

uint8_t button_1_index = 4;
uint8_t button_2_index = 5;
uint8_t button_3_index = 6;
uint8_t button_4_index = 7;
uint8_t button_5_index = 8;
uint8_t button_6_index = 9;

uint8_t button_big_index = 10;

void setup()
{
  pinMode(RXLED, OUTPUT);
  pinMode(button_up, INPUT_PULLUP);
  pinMode(button_down, INPUT_PULLUP);
  pinMode(button_left, INPUT_PULLUP);
  pinMode(button_right, INPUT_PULLUP);
  
  pinMode(button_1, INPUT_PULLUP);
  pinMode(button_2, INPUT_PULLUP);
  pinMode(button_3, INPUT_PULLUP);
  pinMode(button_4, INPUT_PULLUP);
  pinMode(button_5, INPUT_PULLUP);
  pinMode(button_6, INPUT_PULLUP);

  pinMode(button_big, INPUT_PULLUP);
  
}

void loop()
{
  // Read current state
  // Inverting logic since buttons are pulled up
  button_up_state = !digitalRead(button_up); 
  button_down_state = !digitalRead(button_down); 
  button_left_state = !digitalRead(button_left); 
  button_right_state = !digitalRead(button_right); 
  
  button_1_state = !digitalRead(button_1); 
  button_2_state = !digitalRead(button_2); 
  button_3_state = !digitalRead(button_3); 
  button_4_state = !digitalRead(button_4); 
  button_5_state = !digitalRead(button_5); 
  button_6_state = !digitalRead(button_6); 
  
  button_big_state = !digitalRead(button_big);
  
  // Set all buttons' state
  gp.setButtonState(button_up_index, button_up_state);
  gp.setButtonState(button_down_index, button_down_state);
  gp.setButtonState(button_left_index, button_left_state);  
  gp.setButtonState(button_right_index, button_right_state);
  
  gp.setButtonState(button_1_index, button_1_state);
  gp.setButtonState(button_2_index, button_2_state);
  gp.setButtonState(button_3_index, button_3_state);
  gp.setButtonState(button_4_index, button_4_state);
  gp.setButtonState(button_5_index, button_5_state);
  gp.setButtonState(button_6_index, button_6_state);

  gp.setButtonState(button_big_index, button_big_state);
  
  delay(20);
  
  // Restore buttons
  if(button_up_state)
    button_up_state = !button_up_state;
  if(button_down_state)
    button_down_state = !button_down_state;
  if(button_left_state)
    button_left_state = !button_left_state;
  if(button_right_state)
    button_right_state = !button_right_state;
    
  if(button_1_state)
    button_1_state = !button_1_state;
  if(button_2_state)
    button_2_state = !button_2_state;
  if(button_3_state)
    button_3_state = !button_3_state;
  if(button_4_state)
    button_4_state = !button_4_state;
  if(button_5_state)
    button_5_state = !button_5_state;
  if(button_6_state)
    button_6_state = !button_6_state;
    
  if(button_big_state)
    button_big_state = !button_big_state;

}
