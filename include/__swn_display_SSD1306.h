#pragma once

#include "SSD1306.h" // legacy include: `#include "SSD1306.h"`

#include <__swn_system.h>

namespace swn
{
  class DisplayRenderer;
  class DisplaySSD1306;

  class DisplaySSD1306
  {
  private:
    SSD1306  _display;
    DisplayRenderer *_renderer;
  public:
    DisplaySSD1306(uint8_t _address, uint8_t _sda, uint8_t _scl);
    virtual ~DisplaySSD1306();

    DisplayRenderer* GetDisplayRenderer(void);
    void SetDisplayRenderer(DisplayRenderer* rendrer);
    SSD1306& GetDisplay(void);
  };
  //////////

  //////////
  class DisplayRenderer : public obj
  {
    friend class DisplaySSD1306;
  private:

    DisplaySSD1306  *_display;
    bool _need_update;
  
  public:
    DisplayRenderer(void);
    ~DisplayRenderer() override;

    void SetDisplay(DisplaySSD1306 *display);
    DisplaySSD1306* GetDisplay(void) noexcept;
    void NeedUpdate(const bool& flag = true) noexcept;
    const bool& GetIsNeedUpdate(void) const noexcept;

    virtual void Render(void);
 
    void Update(const TimeInfo& time) override;
    const char* TypeName(void) override;;
  };



}