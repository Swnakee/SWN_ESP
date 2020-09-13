#include <__swn_subscriber.h>
#include <__swn_event.h>
#include <random>

using namespace std;
using namespace swn;

Subscriber::Subscriber(const std::function<void(Event*, void* data)>& func) :  _ID{size_t(rand())}, _events(), _func(func)
{

}
Subscriber::~Subscriber()
{
    UnSubAll();
}

void Subscriber::Run(Event* event, void* data)
{
    _func(event, data);
}

const bool Subscriber::Sub(Event *event)
{
    for(size_t i = 0; i < _events.size(); i++)
        if(_events[i] == event)
            return true;
    
    _events.push_back(event);
    event->__AddSub(this);
    return true;
}
const bool Subscriber::UnSub(Event *event)
{
    for(size_t i = 0; i < _events.size(); i++)
        if(_events[i] == event)
        {
            _events[i]->__DeleteSub(this);
            _events.erase(_events.begin() + i);
            return true;    
        }
    return false;
}
void Subscriber::UnSubAll(void)
{
    while (!_events.empty())
        UnSub(_events.front());
}

const size_t& Subscriber::ID(void) const noexcept {return _ID;}