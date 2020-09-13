#pragma once

#include <vector>

namespace swn
{
    class Subscriber;

    class Event
    {
        friend class Subscriber;
    private:
        std::vector<Subscriber*> _subs;

        void __AddSub(Subscriber *sub);
        void __DeleteSub(Subscriber *sub);
    public:
        Event();
        ~Event();

        void ClearSubs(void);

        void operator()(void *data = nullptr);
        
    };
}