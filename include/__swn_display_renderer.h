#pragma once

#include "SSD1306.h" 
#include "__swn_subscriber.h"

namespace swn
{
  //////////
    class DisplaySSD1306
    {
    private:
        SSD1306 _display;
    public:
        DisplaySSD1306(uint8_t _address, uint8_t _sda, uint8_t _scl);

        SSD1306* GetDisplay(void) noexcept;
    };

    class DisplayRenderer
    {
    private:
        DisplaySSD1306 *_display;

        Subscriber _sub_render;
    public:
        DisplayRenderer(void);
        virtual ~DisplayRenderer();

        void        SetDisplay(DisplaySSD1306 *display) noexcept;
        DisplaySSD1306*GetDisplay(void) noexcept;

        Subscriber* Sub_Render();

        virtual void Render(void);
    
    };

}