#pragma once

#include <__swn_sys_object.h>

#include <thread>
#include <mutex>
#include <string>
#include <vector>

using namespace std;

namespace swn
{

    class sys
    {
        friend class SysObject;
    private:
        std::vector<SysObject*> _objects;

        void __AddObject(SysObject *obj);
        const bool __DeleteObject(SysObject *obj);
    public:
        sys();
        
        const bool UpdateSystem(void);
    };

}