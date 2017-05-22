#include <Gamepad.h>

//Initializing a Gamepad
Gamepad gp;

/*  Button  | Free    | Paid
    1         Start     Start
    2         Select    -
    3         X         X
    4         A         A
    5         Y         Y
    6         B         B
    Big       -         -
    CCounter  -         Select
               
    Joystick    Big    1 3 5
              button  2 4 6
*/
int RXLED = 17;

// Configuration variables 
static const uint8_t price = 4; //Credit price in 5 cents multiples
static const uint8_t inactivity_time = 5; //Time of inactivity in minutes for the game to be changed

// Button constant definitions
static const uint8_t button_up = 2;
static const uint8_t button_down = 3;
static const uint8_t button_left = 4;
static const uint8_t button_right = 5;

static const uint8_t button_free = 9;
static const uint8_t coin_counter = 7;

static const uint8_t button_1 = A2;
static const uint8_t button_2 = A3;
static const uint8_t button_3 = A0;
static const uint8_t button_4 = 14;
static const uint8_t button_5 = A1;
static const uint8_t button_6 = 15;

//static const uint8_t button_big = 16;

// Button state definitions
bool button_up_state = false;
bool button_down_state = false;
bool button_left_state = false;
bool button_right_state = false;

bool button_free_state = false;

bool button_1_state = false;
bool button_2_state = false;
bool button_3_state = false;
bool button_4_state = false;
bool button_5_state = false;
bool button_6_state = false;

//bool button_big_state = false;

// Button index definitions
uint8_t button_up_index = 0;
uint8_t button_down_index = 1;
uint8_t button_left_index = 2;
uint8_t button_right_index = 3;

uint8_t start_index = 4;
uint8_t select_index = 5;
uint8_t x_index = 6;
uint8_t a_index = 7;
uint8_t y_index = 8;
uint8_t b_index = 9;

//uint8_t button_big_index = 10;

//Coin counter variables
bool free_mode = false;
byte Command = 0;

volatile unsigned long change_time;
volatile unsigned long last_play_time;
volatile unsigned long pulse_time;
volatile byte pulse_count = 0;
volatile byte credit_count = 0;

void setup(){
  
  //Pad setup
  pinMode(RXLED, OUTPUT);
  pinMode(button_up, INPUT_PULLUP);
  pinMode(button_down, INPUT_PULLUP);
  pinMode(button_left, INPUT_PULLUP);
  pinMode(button_right, INPUT_PULLUP);

  pinMode(button_free, INPUT_PULLUP);
  
  pinMode(button_1, INPUT_PULLUP);
  pinMode(button_2, INPUT_PULLUP);
  pinMode(button_3, INPUT_PULLUP);
  pinMode(button_4, INPUT_PULLUP);
  pinMode(button_5, INPUT_PULLUP);
  pinMode(button_6, INPUT_PULLUP);

  //pinMode(button_big, INPUT_PULLUP);
  
  //Coin counter setup
  Serial.begin(9600);
  pinMode(coin_counter, INPUT_PULLUP);
  attachInterrupt(1, coinPulse, RISING);

  change_time = inactivity_time * 60000; //Convert minutes to millis
}

void loop(){

  if(!free_mode)checkCoin();
  
  // Read current state
  // Inverting logic since buttons are pulled up
  button_up_state = !digitalRead(button_up); 
  button_down_state = !digitalRead(button_down); 
  button_left_state = !digitalRead(button_left); 
  button_right_state = !digitalRead(button_right); 

  button_free_state = !digitalRead(button_free);
  
  button_1_state = !digitalRead(button_1); 
  button_2_state = !digitalRead(button_2); 
  button_3_state = !digitalRead(button_3); 
  button_4_state = !digitalRead(button_4); 
  button_5_state = !digitalRead(button_5); 
  button_6_state = !digitalRead(button_6); 

  //button_big_state = !digitalRead(button_big);
  
  if(button_free_state){
    free_mode=(!free_mode);
    Serial.println("Free mode changed to: "+free_mode);
  }

  if(button_up_state||button_down_state||button_left_state||button_right_state||
     button_free_state||button_1_state||button_2_state||button_3_state||button_4_state||
     button_5_state||button_6_state){
        last_play_time = millis();
     }
   
  // Set all buttons' state
  gp.setButtonState(button_up_index, button_up_state);
  gp.setButtonState(button_down_index, button_down_state);
  gp.setButtonState(button_left_index, button_left_state);  
  gp.setButtonState(button_right_index, button_right_state);
  
  gp.setButtonState(start_index, button_1_state);
  if(free_mode){
    gp.setButtonState(select_index, button_2_state);
  }else{
    gp.setButtonState(select_index, useCredit());
  }
  gp.setButtonState(x_index, button_3_state);
  gp.setButtonState(a_index, button_4_state);
  gp.setButtonState(y_index, button_5_state);
  gp.setButtonState(b_index, button_6_state);

  //gp.setButtonState(button_big_index, button_big_state);

  if((last_play_time - millis())>(change_time*1000)){
    changeGame();
  }
  
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

 if(button_free_state)
    button_free_state = !button_free_state;

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
    
//  if(button_big_state)
//    button_big_state = !button_big_state;

}

void coinPulse(){
  pulse_count++;
  Serial.println("Pulse detected, current: "+pulse_count);
  pulse_time = millis();
}
 
bool useCredit(){
  if(credit_count >= price){
    credit_count -= price;
    return(true);
  }
  return(false);
}

void checkCoin(){
  if(pulse_count > 0 && millis() - pulse_time > 200){
    Serial.println("Coin detected, pulses:"+ pulse_count);
    switch(pulse_count){
        case 1: //2 euros
         credit_count+=40;
         Serial.println("2 euros");
        break;
        case 2: //1 euro
         credit_count+=20;
         Serial.println("1 euro");
        break;
        case 3: //50 cents
         credit_count+=10;
         Serial.println("50 cents");
        break;
        case 4: //20 cents
         credit_count+=4;
         Serial.println("20 cents");
        break;
        case 5: //10 cents
         credit_count+=2;
         Serial.println("10 cents");
        break;
        case 6: //5 cents
         credit_count++;
         Serial.println("5 cents");
        break;
    }
    pulse_count = 0;
  }
}

void changeGame(){
  //Execute ordered button combination to exit the game and swap to the next one
  //by a countered switch.
}

