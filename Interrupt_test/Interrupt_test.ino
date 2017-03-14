int pin = 7;
int count = 0;
volatile int var;

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(pin, INPUT_PULLUP);
  attachInterrupt(4,foo,RISING);
  var = 0;
}

void loop() 
{
  // put your main code here, to run repeatedly:
  if(var == 1)
  {
    count += 1;
    Serial.print("Hola ");
    Serial.println(count);
    var = 0;
  }
  delay(500);
}

void foo()
{
  var = 1;
}

