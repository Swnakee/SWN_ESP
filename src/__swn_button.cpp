#include <__swn_button.h>
#include <__swn_sys_object.h>

using namespace swn;

#define DROP_PRESS 60

Button::Button(sys *s, const int8_t& pin, const unsigned long& time_delay_second_press) 
    : SysObject(s),
    _pin{pin}, _status{0}, _count_press{0}, _time_press{0}, _time_second_press{time_delay_second_press},
    _timer_drop(), _timer_un_press_drop(), _timer_second_press(),
    _event_press(), _event_un_press(), _event_second_press()
{
    pinMode(_pin, INPUT);
}

Button::~Button(){}

Event* Button::Event_Press(void)
{
    return &_event_press;
}
Event* Button::Event_Un_Press(void)
{
    return &_event_un_press;
}
Event* Button::Event_Second_Press(void)
{
    return &_event_second_press;
}

const unsigned long Button::GetTimePress(void) const noexcept
{
    if(_status == 2)
        return millis() - _time_press;
    return 0;
}
const int8_t Button::GetCountPress(void) const noexcept
{
    return _count_press;
}
const int8_t Button::GetPin(void) const noexcept
{
    return _pin;
}

void Button::UpdateStatus()
{
    bool buffer_press = digitalRead(_pin);

    if(buffer_press)
    {
        if(_status == 0)
        {
            _status = 1;
            _timer_drop.Start(DROP_PRESS);
        }
        else if(_timer_drop && _status == 1)
        {
            _time_press = millis();
            _status = 2;
            _count_press++;

            if(_count_press == 1)
                _event_press(this);
            else
            {
                _event_press(this);
                _event_second_press(this);
            }
        }
    }
    else
    {
        if(_status == 2)
        {
            _status = 3;
            _timer_un_press_drop.Start(DROP_PRESS);
        }
        else if(_timer_un_press_drop && _status == 3)
        {
            _timer_second_press.Start(_time_second_press);
            _event_un_press(this);
            _status = 0;
        }
        
        if(_timer_second_press)
        {
            _count_press = 0;
            _timer_second_press.Stop();
        }
    }
}

const char* Button::TypeName(void) const noexcept
{
    return "Button";
}