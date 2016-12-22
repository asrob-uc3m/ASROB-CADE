int A, previous_A;
int counter = 0;
float actual_t = 0;
float start_t =0;
float delta_t;
int reset_counter = 0;
bool isACK = true;
bool timerOK = false;

void setup()
{
  Serial.begin(4800);
  pinMode(A0, INPUT);
}


  
void loop()
{
  
  A = analogRead(A0);
  //Serial.println(A);
  if((previous_A  <=5 ) && A > 5){
    if(isACK){
      isACK = false;
      delay(3.6);
    }else{
      counter += 1;
      //Serial.println(counter);
      delay(2.04);
      start_t = 0;
      timerOK=false;
    }
  }
  if((A==previous_A) && (A == 0) && (timerOK == false) && (counter > 0)){
    //Serial.println("Starting timer");
    timerOK = true;
    start_t = millis();
  }
  if(((actual_t - start_t)>500) && (counter > 0) && (start_t > 0)){
    check_coin(counter);
    counter = 0;
    start_t = 0;
    actual_t = 0;
    isACK = false;
    timerOK = false;
    //Serial.println("cleaning...");
  }
  actual_t = millis();
  previous_A = A;
}

void check_coin(int counter){
  Serial.println(counter);
  if(100 <= counter){
    Serial.println("Son 5 centimos");
  }else if((75 <= counter) && (counter < 100)){
    Serial.println("Son 10 centimos");
  }else if((60 <= counter) && (counter < 75)){
    Serial.println("Son 20 centimos");
  }else if((48 <= counter) && (counter < 60)){
    Serial.println("Son 50 centimos");
  }else if((32 <= counter) && (counter < 48)){
    Serial.println("Es 1 euro");
  }else if(counter < 32){
    Serial.println("Son 2 euros");
  }else{
    Serial.println("No se contar");
  }
}



