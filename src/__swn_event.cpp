#include <__swn_subscriber.h>
#include <__swn_event.h>
#include <random>

using namespace std;
using namespace swn;

void Event::__AddSub(Subscriber *sub)
{
    _subs.push_back(sub);
}

void Event::__DeleteSub(Subscriber *sub)
{
    for(size_t i = 0; i < _subs.size(); i++)
        if(_subs[i] == sub)
            _subs.erase(_subs.begin() + i);
}

////////////////

Event::Event() : _subs()
{

}

Event::~Event()
{
    ClearSubs();
}

void Event::ClearSubs(void)
{
    while (!_subs.empty())
    {
        Subscriber *ptr = _subs.front();
        ptr->UnSub(this);
    }
}

void Event::operator()(void *data)
{
    std::vector<Subscriber*> _buffer_subs = _subs;
    for(size_t i = 0; i < _buffer_subs.size(); i++)
        _buffer_subs[i]->Run(this, data);
}