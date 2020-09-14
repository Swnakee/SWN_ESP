#pragma once

#include <Arduino.h>

namespace swn
{

  class Pin
  {
  private:
    int8_t _pin;
    bool _is_enable;

  public:
    Pin(const int8_t & _pin);
    ~Pin();
    void IsEnable(const bool& flag) noexcept;
    void Enable(void) noexcept;
    void Disable(void) noexcept;
    void Invert(void) noexcept;

    const int8_t& GetPin(void) const;
    const bool& IsEnable(void) const;
  };

}