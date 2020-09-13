#pragma once

#include <__swn_sys_object.h>
#include <__swn_event.h>
#include <__swn_timer.h>

using namespace std;

namespace swn
{

    class EventTimer : public SysObject
    {
    private:
        Event _event_tick;

        swn::Timer _timer;
    public:
        EventTimer(const unsigned long& ms, sys *s);
        ~EventTimer() override;

        Event* Event_Tick(void);
        Timer& GetTimer(void);

        void UpdateStatus() override;

        const char* TypeName(void) const noexcept override; 
    };

}