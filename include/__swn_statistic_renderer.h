#pragma once

#include <__swn_display_SSD1306.h>

#define CONSOLE_RENDERER_COUNT_LINES 7

namespace swn
{
    class StatisticRenderer : public DisplayRenderer
    {
    public:
        StatisticRenderer();
        ~StatisticRenderer() override;

        void Render(void) override;

        void Update(const TimeInfo& time) override;

        const char* TypeName(void) override;
    };

}
   

