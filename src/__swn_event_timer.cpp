#include <__swn_event_timer.h>

using namespace std;
using namespace swn;


EventTimer::EventTimer(const unsigned long& ms, sys *s) : SysObject(s), _timer()
{
    _timer.Start(ms);
}
        
EventTimer::~EventTimer()
{

}

Event* EventTimer::Event_Tick(void)
{
    return &_event_tick;
}

void EventTimer::UpdateStatus()
{
    if(_timer)
    {
        _event_tick();
        _timer.Restart();
    }
}

Timer& EventTimer::GetTimer(void)
{
    return _timer;
}

const char* EventTimer::TypeName(void) const noexcept
{
    return "EventTimer";
}