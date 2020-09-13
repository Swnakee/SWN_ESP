#pragma once

#include <__swn_timer.h>
#include <__swn_system.h>
#include <__swn_event.h>

namespace swn
{
  class Button : public SysObject
  {
    public:

    private:
      int8_t _pin;
      int8_t _status;
      int8_t _count_press;

      unsigned long _time_press;
      unsigned long _time_second_press;
      Timer _timer_drop;
      Timer _timer_un_press_drop;
      Timer _timer_second_press;

      swn::Event _event_press;
      swn::Event _event_un_press;
      swn::Event _event_second_press;
    public:
      Button(sys *s, const int8_t& pin, const unsigned long& time_delay_second_press = 700);
      virtual ~Button();

      Event* Event_Press(void);
      Event* Event_Un_Press(void);
      Event* Event_Second_Press(void);

      const unsigned long GetTimePress(void) const noexcept; 
      const int8_t GetCountPress(void) const noexcept; 
      const int8_t GetPin(void) const noexcept;

      void UpdateStatus(void) override;
      const char* TypeName(void) const noexcept override; 
    };

}