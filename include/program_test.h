#pragma once

#include <swn.h>

using namespace swn;

class Looper : public SysObject
{
public:
  DisplaySSD1306 display;

  Button *but1;
  Button *but2;

  ConcoleRenderer *console;
  Graph *graph;
  DisplayRenderer *displaye_null;

  Timer timer_01;
  Timer timer_02;
  Timer timer_03;

public:

  Looper() : SysObject(), display(0x3c, 23, 22)  { }

  ~Looper() 
  {
    // console->Delete();
    // graph->Delete();
  }

  void Start()
  {
    console = sys::CreateObj<ConcoleRenderer>();

    sys::AddEventCreateObj({"Serial", [this](const String& name) {(*this->console) << "Create: " << name << endl;}});
    sys::AddEventDeleteObj({"Serial", [this](const String& name) {(*this->console) << "Delete: " << name << endl;}});

    
    graph = sys::CreateObj<Graph>(128, 0, 0);
    displaye_null = sys::CreateObj<DisplayRenderer>();
    //dis->SetDisplayRenderer(graph);

    // System::GetConsole()->SetFloatResolution(6);
    // ConcoleRenderer &cmd = *System::GetConsole();

    display.SetDisplayRenderer(graph);

    but1 = sys::CreateObj<Button>(27);
    but2 = sys::CreateObj<Button>(26);

    timer_01.Start(1000);
    timer_03.Start(2000);
    timer_02.Start(100);
  }

  void FirstUpdate(const TimeInfo& time) 
  {
    
  };

  void Update(const TimeInfo& time) 
  {

    //graph->Add(time.GetTimeMax());
    //ConcoleRenderer &cmd = *System::GetConsole();
   
   
    if(but1->IsFirstPress())
    {
      display.SetDisplayRenderer(graph);  
    }
    if(but2->IsFirstPress())
    {
      display.SetDisplayRenderer(console);  
    }

    if(timer_02)
    {
      static bool flag = false;
      digitalWrite(14, flag);
      flag = !flag;
      timer_02.Restart();
    }
  }
  
  const char* TypeName(void) override {return "Looper";}

};