#pragma once

#include <__swn_display_SSD1306.h>
#include <map>

using namespace std;

namespace swn
{

    class MenuSwitcher
    {
    private:
        DisplaySSD1306 *_display;
        std::vector<std::pair<String, DisplayRenderer*>> _menu;
        size_t _offset;

        void __update_menu(void);
    public:
        MenuSwitcher(DisplaySSD1306 *_display = nullptr);

        DisplaySSD1306* GetDisplay(void);
        void SetDisplay(DisplaySSD1306 *new_display);

        const bool AddMenu(const String& name, DisplayRenderer* ptr);
        DisplayRenderer* GetMeny(const String& name);
        const bool DeleteMenu(const String& name);
        
        const bool SwitchTo(const String& name);
        void Right(void);
        void Left(void);
    };


}