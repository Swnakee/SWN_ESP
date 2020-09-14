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
DisplaySSD1306 *display;
DisplayRenderer dis;
ConcoleRenderer cmd;
Graph graph(GRAPH_X, 0, 1);

Button but1(&s, BUT1);
Button but2(&s, BUT2);

size_t start_mic = 0;
size_t mic_count = 0;
size_t mic = 0;

EventTimer *ev_timer;


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

  graph.SetDisplay(display);
  Subscriber *event_timer = new Subscriber([](Event *ev, void*data)
  {
      graph.Add( ((float)mic / (float)mic_count)/1000.0f );
      mic_count = mic = 0;

      graph.NeedUpdate();
      graph.Render();
  });
  ev_timer = new EventTimer(25, &s);
  event_timer->Sub(ev_timer->Event_Tick());
}



void loop() 
{
  s.UpdateSystem();
  
  mic += micros() - start_mic;
  mic_count++;
  start_mic = micros();
}