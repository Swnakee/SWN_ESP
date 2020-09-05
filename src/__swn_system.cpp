#include <__swn_system.h>
#include <__swn_timer.h>

#include <__swn_console_renderer.h>

using namespace swn;


StringEventArgs::StringEventArgs(const String& str) : _str{str}{}
StringEventArgs::~StringEventArgs() {}

const String& StringEventArgs::GetString(void) const noexcept
{
    return _str;
}

////////////////////

TimeInfo::TimeInfo() : TimeInfo::TimeInfo(0,0){}
TimeInfo::TimeInfo(const unsigned long& mil, const float& time) : _micros{mil}, _time{time}, _counter{0}, _max_counter{1000}{}
TimeInfo::TimeInfo(const TimeInfo& info)
{
    _micros = info._micros;
    _time = info._time;
    _counter = info._counter;
    _max_counter = info._max_counter;
}
TimeInfo& TimeInfo::operator = (const TimeInfo& info)
{
    _micros = info._micros;
    _time = info._time;
    _counter = info._counter;
    _max_counter = info._max_counter;
    return *this;
}

void TimeInfo::FirstUpdate(void)
{
    _time = (micros() - _micros) / ((float)1000000);
    _micros = micros();
    
    _buffer_time_max = _time > _buffer_time_max ? _time : _buffer_time_max;
    _buffer_time_min = _time < _buffer_time_min ? _time : _buffer_time_min;
    if(_counter >= _max_counter)
    {
        _time_max = _buffer_time_max;
        _time_min = _buffer_time_min;
        _buffer_time_max = _buffer_time_min = _time;

        _counter = 0;
    }
    _counter++;
}
void TimeInfo::Update(void)
{
    _time = (micros() - _micros) / ((float)1000000);
    _micros = micros();
    
    _buffer_time_max = _time > _buffer_time_max ? _time : _buffer_time_max;
    _buffer_time_min = _time < _buffer_time_min ? _time : _buffer_time_min;
    if(_counter >= _max_counter)
    {
        _time_max = _buffer_time_max;
        _time_min = _buffer_time_min;
        _buffer_time_max = _buffer_time_min = _time;

        _counter = 0;
    }
    _counter++;
}

const int16_t& TimeInfo::GetCounter(void) const { return _counter; }
const int16_t& TimeInfo::GetMaxCounter(void) const { return _max_counter; }
void TimeInfo::SetMaxCounter(const int16_t& new_max_counter) { _max_counter = new_max_counter; }
const float& TimeInfo::GetDeltaTime(void) const {return _time;}
const float& TimeInfo::GetTimeMax(void) const {return _time_max;}
const float& TimeInfo::GetTimeMin(void) const {return _time_min;}

///////////////////////

SysObject::SysObject() : _is_delete{false}{}
SysObject::~SysObject(){}

void SysObject::Delete(void) {_is_delete = true;}
const bool& SysObject::IsDelete(void) const { return _is_delete; }

///////////////////////
///////////////////////
///////////////////////
///
std::vector<SysObject*> System::_sys_obj;
EventManger System::_event_create_obj;
EventManger System::_event_delete_obj;
TimeInfo System::_time_info;
///
Timer update_timer;
///
void System::Init(void)
{
    update_timer.Start(1000/60);
}
void System::Update()
{
    _time_info.FirstUpdate();
    
    for(size_t i = 0; i < _sys_obj.size(); i++)
        _sys_obj[i]->FirstUpdate(_time_info);

    if(update_timer)
    {
        //_time_info.Update();

        for(size_t i = 0; i < _sys_obj.size(); i++)
            _sys_obj[i]->Update(_time_info);
        for(size_t i = 0; i < _sys_obj.size(); i++)
            _sys_obj[i]->LastUpdate(_time_info);
        
        update_timer.Restart();
    }

    for(size_t i = 0; i < _sys_obj.size();i++)
    {
        if(_sys_obj[i]->IsDelete())
        {
            _event_delete_obj(StringEventArgs(_sys_obj[i]->TypeName()));
            delete _sys_obj[i];
            _sys_obj.erase(_sys_obj.begin() + i);
        }
     
    }

}

std::vector<SysObject*>& System::GetSysObject() 
{ 
    return _sys_obj; 
}
const TimeInfo& System::GetTimeInfo(void)
{ 
    return _time_info; 
}
void SetTimerUpdate(const unsigned long& new_ms)
{
    update_timer.Start(new_ms);
}

const bool System::AddEventCreateObj(const pair<String, Event>& func)
{
    return _event_create_obj.AddEvent(func);
}
const bool System::AddEventDeleteObj(const pair<String, Event>& func)
{
    return _event_delete_obj.AddEvent(func);
}
const bool System::DeleteEventCreateObj(const String& name)
{
    return _event_create_obj.DeleteEvent(name);
}
const bool System::DeleteEventDeleteObj(const String& name)
{
    return _event_delete_obj.DeleteEvent(name);
}
void System::DeleteAllEventCreateObj(void)
{
    _event_create_obj.DeleteAllEvent();
}
void System::DeleteAllEventDeleteObj(void)
{
    _event_delete_obj.DeleteAllEvent();
}