#pragma once 

#include <swn.h>

using namespace std;
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
        EventTimer screen_timer_update;
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
            :   SysObject(s), screen_graph(GRAPH_X, 0, 1), screen_timer_update(100, s),
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
        }

        void Init()
        {
            display = new DisplaySSD1306(0x3c, 23, 22);
            screen_cmd.SetDisplay(display);
            screen_graph.SetDisplay(display);
            screen_menu.SetDisplay(display);
            pinMode(LED, OUTPUT);

            screen_menu.Sub_Render()->Sub(screen_timer_update.Event_Tick());
            screen_menu.AddRenderer("CMD", &screen_cmd);
            screen_menu.AddRenderer("GRAPH", &screen_graph);
            screen_menu.SwitchTo("GRAPH");

            bu1_press = new Subscriber([this](Event*,void*) { _but1_press = true; });
            bu2_press = new Subscriber([this](Event*,void*) { _but2_press = true; });
            bu1_un_press = new Subscriber([this](Event*,void*) { _but1_press = false; });
            bu2_un_press = new Subscriber([this](Event*,void*) { _but2_press = false; });
            bu1_press->Sub(but1.Event_Press());
            bu2_press->Sub(but2.Event_Press());
            bu1_un_press->Sub(but1.Event_Un_Press());
            bu2_un_press->Sub(but2.Event_Un_Press());

            graph_update_timer.Start(25);
        }

        void UpdateStatus() override
        {
            // graph update
            count_microsec_graph++;
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

            if(_but1_press && _but2_press)
            {
                _but1_press = _but2_press = false;
                screen_menu.Right();
            }
        }

    };
}