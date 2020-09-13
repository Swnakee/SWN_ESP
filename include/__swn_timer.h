#pragma once

#include <Arduino.h>

namespace swn
{
  class Timer
  {
    private:
      unsigned long _to_time;
      unsigned long _time_sleep;
      bool _stop;
    public:
      Timer();
      ~Timer();

      void Start(const unsigned long & time_ms) noexcept;
      void Restart() noexcept;
      void Restart(const unsigned long & time_ms) noexcept;
      void Stop(void) noexcept;

      const bool IsTick() const noexcept;

      operator bool() const noexcept;
  };

}