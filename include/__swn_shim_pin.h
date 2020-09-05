#pragma once

#include <Arduino.h>


namespace swn
{

  class ShimPin
  {
  private:

    int8_t _ledChannel;
    int _Hz;
    int8_t _resolution;

  public:

    ShimPin(const int8_t& ledChanel, const int& Hz, const int8_t& resolution);
    ShimPin(const int8_t& pin, const int8_t& ledChanel, const int& Hz, const int8_t& resolution);

    void Reinit(const int8_t& ledChanel, const int& Hz, const int8_t& resolution);
    void Reinit(const int& Hz, const int8_t& resolution);
    void Reinit(const int& Hz);

    void AttachPin(const int8_t& pin);
    void DettachPin(const int8_t& pin);

    void Write(const int32_t& val);
    const int32_t Read();
    

    const int8_t& GetLedChanel(void) const;
    const int& GetHz(void) const;
    const int8_t& GetResolution(void) const;

  };

}