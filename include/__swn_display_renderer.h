#pragma once

#include "SSD1306.h" 

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
        bool _need_update;
    public:
        DisplayRenderer(void);
        virtual ~DisplayRenderer();

        void        SetDisplay(DisplaySSD1306 *display) noexcept;
        DisplaySSD1306*GetDisplay(void) noexcept;
        void        NeedUpdate(const bool& flag = true) noexcept;
        const bool& GetIsNeedUpdate(void) const noexcept;

        virtual void Render(void);
    
    };

}