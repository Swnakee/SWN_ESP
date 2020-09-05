#include <__swn_event.h>

using namespace std;
using namespace swn;


EventArgs::EventArgs(){}
EventArgs::~EventArgs(){}

///////////////////////////


const bool EventManger::AddEvent(const pair<String, Event>& func)
{
    for(size_t i = 0; i < _events.size(); i++)
        if(_events[i].first == func.first)
            return false;
    _events.push_back(func);
    return true;
}
const bool EventManger::DeleteEvent(const String& name)
{
    for(size_t i = 0; i < _events.size(); i++)
        if(_events[i].first == name)
        {
            _events.erase(_events.begin() + i);
            return true;
        }
    return false;
}
void EventManger::DeleteAllEvent(void)
{
    _events.clear();
}

void EventManger::operator()(const EventArgs& param)
{
    if(_events.empty()) return;

    EventArgs &event = const_cast<EventArgs&>(param);
    for(size_t i = 0; i < _events.size(); i++)
        _events[i].second(&event);
}