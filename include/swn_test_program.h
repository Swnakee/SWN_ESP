#pragma once 

#include <swn.h>

using namespace std;
using namespace std::placeholders;
using namespace swn;

namespace swn
{
    int8_t LED = 14;
    int8_t BUT1 = 27;
    int8_t BUT2 = 26;
    
    class SwnTestProgram : public SysObject
    {
    private:

        //screen param
        DisplaySSD1306 *display;
        ConcoleRenderer screen_cmd;
        Graph screen_graph;
        MenuSwitcher screen_menu;
        //graph var
        size_t microsec_graph = 0;
        size_t count_microsec_graph = 0;
        size_t last_microsec_graph = 0;
        Timer graph_update_timer;
        //
        EventTimer event_timer_01;
        Subscriber *event_timer_01_update;
        //
        //button
        Button but1;
        Button but2;
        Subscriber *bu1_press;
        Subscriber *bu2_press;
        Subscriber *bu1_un_press;
        Subscriber *bu2_un_press;
        bool _but1_press;
        bool _but2_press;
        //

    public:
        SwnTestProgram(sys *s) 
            :   SysObject(s), screen_graph(GRAPH_X, 0, 1), event_timer_01(1000/60, s),
                but1(s, BUT1), but2(s, BUT2), bu1_press{nullptr}, bu2_press{nullptr}, bu1_un_press{nullptr}, bu2_un_press{nullptr},
                _but1_press{false}, _but2_press{false}
        {
            Init();
        }

        ~SwnTestProgram() override
        {
            delete display;
            delete bu1_press;
            delete bu2_press;
            delete bu1_un_press;
            delete bu2_un_press;
            delete event_timer_01_update;
        }

        void Init()
        {
            display = new DisplaySSD1306(0x3c, 23, 22);
            screen_cmd.SetDisplay(display);
            screen_graph.SetDisplay(display);
            screen_menu.SetDisplay(display);
            pinMode(LED, OUTPUT);

            screen_menu.AddRenderer("CMD", &screen_cmd);
            screen_menu.AddRenderer("GRAPH", &screen_graph);
            screen_menu.SwitchTo("GRAPH");

            bu1_press = new Subscriber([this](Event*,void*) { _but1_press = true; screen_cmd << "But1 prees" << endl << upd; });
            bu2_press = new Subscriber([this](Event*,void*) { _but2_press = true; screen_cmd << "But2 prees" << endl << upd; });
            bu1_un_press = new Subscriber([this](Event*,void*) { _but1_press = false; });
            bu2_un_press = new Subscriber([this](Event*,void*) { _but2_press = false; });
            bu1_press->Sub(but1.Event_Press());
            bu2_press->Sub(but2.Event_Press());
            bu1_un_press->Sub(but1.Event_Un_Press());
            bu2_un_press->Sub(but2.Event_Un_Press());

            graph_update_timer.Start(25);

            event_timer_01_update = new Subscriber(std::bind(&SwnTestProgram::EventTimer01, this, _1, _2));
            event_timer_01_update->Sub(event_timer_01.Event_Tick());
        }
        void EventTimer01(Event*, void*)
        {
            // graph update
            if(graph_update_timer)
            {
                screen_graph.Add( (micros() - last_microsec_graph) / (float)count_microsec_graph / 1000.0f / 1000.0f );
                last_microsec_graph = micros();
                count_microsec_graph = 0;

                if(screen_menu.GetActiveRendrer() == &screen_graph) 
                    screen_menu.Render();

                graph_update_timer.Restart();
            }
            // --------------
        }
        void UpdateStatus() override
        {
            // graph update
            count_microsec_graph++;
            // --------------

            if(_but1_press && _but2_press)
            {
                _but1_press = _but2_press = false;
                screen_menu.Right();
            }
        }

    };
}