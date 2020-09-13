#pragma once

#include <vector>
#include <functional>

namespace swn
{
    class Event;
    class Subscriber
    {
    private:
        std::size_t _ID;
        std::vector<Event*> _events;
        std::function<void(Event*, void* data)> _func;
    public:
        Subscriber(const std::function<void(Event*, void* data)>& func);
        virtual ~Subscriber();

        void Run(Event*, void* data);

        const bool Sub(Event *event);
        const bool UnSub(Event *event);
        void UnSubAll(void);

        const size_t& ID(void) const noexcept;
    };
}