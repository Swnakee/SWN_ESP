#include <Arduino.h> 

#include <thread>
#include <typeinfo> 
#include <functional>

#include <swn.h>


using namespace swn;
using namespace std::placeholders;
using namespace std;

int8_t LED = 14;
int8_t BUT1 = 27;
int8_t BUT2 = 26;

sys s;

// swn::ConcoleRenderer cmd;
Subscriber sub([&](Event*, void*)
{
  digitalWrite(LED, !digitalRead(LED));
});

DisplaySSD1306 *display;
DisplayRenderer dis;
ConcoleRenderer cmd;

Button but1(&s, BUT1);
Button but2(&s, BUT2);


void setup() 
{
  Serial.begin(115200);
  delay(100);

  pinMode(LED, OUTPUT);

  display = new DisplaySSD1306(0x3c, 23, 22);

  cmd.SetDisplay(display);
  cmd.NeedUpdate();

  Subscriber *press = new Subscriber([](Event *ev, void*data)
  {
    Button *but = reinterpret_cast<Button*>(data);
    Serial.println("Button press, pin: " + String(but->GetPin()));
  });

  Subscriber *un_press = new Subscriber([](Event *ev, void*data)
  {
    Button *but = reinterpret_cast<Button*>(data);
    Serial.println("Button un press, pin: " + String(but->GetPin()));
  });

  Subscriber *second_press = new Subscriber([](Event *ev, void*data)
  {
    Button *but = reinterpret_cast<Button*>(data);
    Serial.println("Button second press, count: " + String(but->GetCountPress()));
  });

  press->Sub(but1.Event_Press());
  un_press->Sub(but1.Event_Un_Press());
  second_press->Sub(but1.Event_Second_Press());

  press->Sub(but2.Event_Press());
  un_press->Sub(but2.Event_Un_Press());
  second_press->Sub(but2.Event_Second_Press());
}

void loop() 
{
  s.UpdateSystem();
  static int i = 0;
  
  
}