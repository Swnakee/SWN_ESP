#pragma once

#include <__swn_timer.h>
#include <__swn_system.h>

namespace swn
{

  class Button : public SysObject
  {
    private:
      int8_t _pin;

      int8_t _status;

      unsigned long _timer_press;
      int8_t _count_press;
      int32_t _info_count_press;

      Timer _timer_mistake_press;
      Timer _timer_second_press;
      unsigned long _time_delay_second_press;

      bool _is_first_press;
      bool _is_unpress;
    public:
      Button(const int8_t& pin, const unsigned long& time_delay_second_press = 700);
      
      void FirstUpdate(const TimeInfo& time) override;
      void LastUpdate(const TimeInfo& time) override;
      const char* TypeName(void) override;

      const unsigned long& GetTimeDelaySecondPress(void);
      void SetTimeDelaySecondPress(const unsigned long& new_time);
      const int8_t& GetPin(void);
      const bool IsPress(void);
      const unsigned long GetTimePress(void);
      const int8_t& GetCountPress(void);
      const int32_t& GetInfoCountPress(void);
      const bool Trigger(void);
      const bool& IsFirstPress(void) const;
      const bool& IsUnpressPress(void) const;

  };

}