#include <Arduino.h>

#include <swn.h>
#include <program_test.h>

using namespace swn;

int8_t LED = 14;
bool LED_VAL = false;
int8_t BUT1 = 27;
int8_t BUT2 = 26;




void setup() 
{
  Serial.begin(9600);
  delay(100);

  pinMode(LED, OUTPUT);

  sys::Init();
  sys::CreateObj<Looper>();
}

void loop() 
{
  sys::Update();
}