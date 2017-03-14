volatile byte CoinPulseCount = 0;
byte NewCoinInserted;
byte Command = 0;
int OpticalCountPin = 2;
volatile unsigned long PulseTime;
volatile byte CreditCount = 0;
volatile byte Credits;

 void setup(){ 
  Serial.begin(9600);
  pinMode(OpticalCountPin, INPUT);
  attachInterrupt(1, CoinPulse, RISING);
 }
 
 void loop(){
  if(CoinPulseCount > 0 && millis() - PulseTime > 200){
    Serial.println("Hop");
    NewCoinInserted = CoinPulseCount;
    CoinPulseCount = 0;
  }
    switch(NewCoinInserted){
      case 1: //2 eypos
       CreditCount+=40;
       Serial.println("2 eypos");
       NewCoinInserted = 0;
      break;
      case 2: //1 eypo
       CreditCount+=20;
       Serial.println("1 eypo");
       NewCoinInserted = 0;
      break;
      case 3: //50cents
       CreditCount+=10;
       Serial.println("50cents");
       NewCoinInserted = 0;
      break;
      case 4: //20cents
       CreditCount+=4;
       Serial.println("20cents");
       NewCoinInserted = 0;
      break;
      case 5: //10cents
       CreditCount+=2;
       Serial.println("10cents");
       NewCoinInserted = 0;
      break;
      case 6: //5cents
       CreditCount+=1;
       Serial.println("5cents");
       NewCoinInserted = 0;
      break;
    }
  
  }
  
 void CoinPulse(){
  CoinPulseCount++;
  Serial.println("Pulso");
  PulseTime = millis();
 }
 void UseCredit(){
  Credits=CreditCount/4;
  CreditCount=CreditCount%4;
  //TO DO: PUSH CREDIT_BUTTON x "Credits" TIMES
  Credits=0;
 }
 
