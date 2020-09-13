#include <__swn_sys_object.h>
#include <__swn_system.h>

#include <Arduino.h>

using namespace std;
using namespace swn;

SysObject::SysObject(sys *s) : _s{s}
{
    _s->__AddObject(this);
}

SysObject::~SysObject()
{
    if(!_s->__DeleteObject(this))
       Serial.println("System error delete, name: " + String(this->TypeName())); 
}

const char* SysObject::TypeName(void) const noexcept
{
    return "SysObject";
}