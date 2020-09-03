#include <__swn_timer.h>

using namespace swn;


Timer::Timer() :  _to_time{0}, _time_sleep{0}, _stop{true} {}

Timer::~Timer() {}

void Timer::Start(const unsigned long & time_ms)
{
    _time_sleep = time_ms;
    _to_time = millis() + _time_sleep;
    _stop = false;
}

void Timer::Restart()
{
    _to_time = millis() + _time_sleep;
    _stop = false;
}

void Timer::Restart(const unsigned long & time_ms)
{
    Start(time_ms);
}

void Timer::Stop()
{
    _stop = true;
}

const bool Timer::IsTick() const noexcept 
{
    if(_stop) return false;
    return millis() >= _to_time ? true : false;
}

Timer::operator bool() const noexcept 
{
    return IsTick();
}