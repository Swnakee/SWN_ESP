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
  StatisticRenderer *statistic;

  Timer timer_01;
  Timer timer_02;
  Timer timer_03;

  MenuSwitcher menu;

public:

  Looper() : SysObject(), display(0x3c, 23, 22)  { }

  ~Looper() 
  {
    // console->Delete();
    // graph->Delete();
  }

  void Start()
  {
    menu.SetDisplay(&display);

    console = sys::CreateObj<ConcoleRenderer>();
    sys::AddEventCreateObj({"Cmd", [this](EventArgs* name)  { (*this->console) << "Create: "<< static_cast<StringEventArgs*>(name)->GetString() << endl; }});
    sys::AddEventDeleteObj({"Cmd", [this](EventArgs* name)  { (*this->console) << "Delete: "<< static_cast<StringEventArgs*>(name)->GetString() << endl; }});

    
    graph = sys::CreateObj<Graph>(128, 0, 0);
    displaye_null = sys::CreateObj<DisplayRenderer>();
    statistic = sys::CreateObj<StatisticRenderer>();

    menu.AddMenu("Console", console);
    menu.AddMenu("Graph", graph);
    menu.AddMenu("Stat", statistic);
    

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
    
    static bool flag = true;
    if(but1->IsPress() && but2->IsPress() && flag)
    {
      menu.Right(); 
      flag = false;
    }
    if(but1->IsUnpressPress() && but2->IsUnpressPress()) flag = true;

  
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