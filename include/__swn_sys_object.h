#pragma once

#include <string>

using namespace std;

namespace swn
{
    class sys;

    class SysObject
    {
    private:
        sys *_s;
    public:    
        SysObject(sys *s);
        virtual ~SysObject();

        virtual void UpdateStatus() = 0;

        virtual const char* TypeName(void) const noexcept; 
    };
}