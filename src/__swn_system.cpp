 #include <__swn_system.h>

#include <Arduino.h>

using namespace std;
using namespace swn;


void sys::__AddObject(SysObject *obj)
{
    _objects.push_back(obj);
    Serial.println("Create: " + String(obj->TypeName()));
}

const bool sys::__DeleteObject(SysObject *obj)
{
    for(size_t i = 0; i < _objects.size(); i++)
        if(_objects[i] == obj)
        {
            Serial.println("Delete: " + String(_objects[i]->TypeName()));
            _objects.erase(_objects.begin() + i);
            return true;
        }

    return false;
}


sys::sys() : _objects()
{

}


const bool sys::UpdateSystem(void)
{
    for(size_t i = 0; i < _objects.size(); i++)
    {
        _objects[i]->UpdateStatus();
    }
    return true;
}

