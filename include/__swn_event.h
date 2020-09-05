#pragma once

#include <vector>
#include <functional>
#include <Arduino.h>

using namespace std;

namespace swn
{
    class EventArgs;
    class EventManger;
    typedef std::function<void(EventArgs*)> Event;

    class EventArgs
    {
    public:
        EventArgs();
        virtual ~EventArgs();
    };

    class EventManger
    {
    private:
        vector< pair<String, Event> > _events;
    public:
        const bool AddEvent(const pair<String, Event>& func);
        const bool DeleteEvent(const String& name);
        void DeleteAllEvent(void);

        void operator()(const EventArgs& param);
    };

}
   

