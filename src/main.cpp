#include <Arduino.h> 

#include <thread>
#include <typeinfo> 
#include <functional>

#include <swn.h>
#include <swn_test_program.h>


using namespace swn;
using namespace std::placeholders;
using namespace std;


sys s;
SwnTestProgram *testProgram;

void setup() 
{
  Serial.begin(115200);
  delay(100);

  testProgram = new SwnTestProgram(&s);
}



void loop() 
{
  s.UpdateSystem();
}