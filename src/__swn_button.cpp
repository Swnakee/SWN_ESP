#include <__swn_button.h>

using namespace swn;


Button::Button(const int8_t& pin, const unsigned long& time_delay_second_press) 
    : _pin{pin}, _status{0}, _timer_press{0}, _count_press{0}, 
    _info_count_press{0}, _time_delay_second_press{time_delay_second_press},
    _is_first_press{false}, _is_unpress{false}
{
    pinMode(_pin, INPUT);
}
      
void Button::FirstUpdate(const TimeInfo& time)
{
    
    if(digitalRead(_pin) == 1)
    {
        if(_status == 0)
        {
            _status = 1;
            _timer_mistake_press.Start(20);
        }
        else if(_timer_mistake_press && _status == 1)
        {
            _is_first_press = true;
            
            _status = 2;

            _timer_press = millis();
            _info_count_press++;

            if(!_timer_second_press)
            {
                _count_press++;  
                _timer_second_press.Stop();
            }
            else
                _count_press = 1;  
        }
    }
    else 
    {
        if(_status == 1)
            _status = 0;
        else if(_status == 2)
        {
            _status = 0;
            _timer_press = 0;
            _timer_second_press.Start(_time_delay_second_press);
        }
        _is_unpress = true;
    }

    if(_timer_second_press)
    {
        _count_press = 0; 
        _timer_second_press.Stop();   
    }
}

void Button::LastUpdate(const TimeInfo& time)
{
    _is_first_press = _is_unpress = false;
}

const char* Button::TypeName(void) {return "Button"; }


const unsigned long& Button::GetTimeDelaySecondPress(void) {return _time_delay_second_press;}
void Button::SetTimeDelaySecondPress(const unsigned long& new_time) {_time_delay_second_press = new_time;}
const int8_t& Button::GetPin(void) {return _pin;}
const bool Button::IsPress(void) {return _status == 2 ? true : false;}
const unsigned long Button::GetTimePress(void) {return _status == 2 ? millis() - _timer_press : 0;}
const int8_t& Button::GetCountPress(void) {return _count_press;}
const int32_t& Button::GetInfoCountPress(void) {return _info_count_press;}
const bool Button::Trigger(void) {return _info_count_press%2 == 1 ? true : false;}


const bool& Button::IsFirstPress(void) const { return _is_first_press; }
const bool& Button::IsUnpressPress(void) const { return _is_unpress; }