#pragma once

#include <vector>
#include <Arduino.h>
#include "__swn_display_renderer.h"

using namespace std;

namespace swn
{
    class DisplayRenderer;

    class MenuSwitcher : public DisplayRenderer
    {
    private:
        std::vector<std::pair<String, DisplayRenderer*>> _menu;
        size_t _offset;
        bool _is_init_menu;
    public:
        MenuSwitcher();
        ~MenuSwitcher() override;

        const bool          AddRenderer(const String& name, DisplayRenderer* ptr);
        DisplayRenderer*    GetRenderer(const String& name);
        String              GetActiveRendrerName(void) const noexcept; 
        DisplayRenderer*    GetActiveRendrer(void) const noexcept; 
        const bool          DeleteRenderer(const String& name);
        void                DeleteAllRenderer(void);
        
        const bool SwitchTo(const String& name);
        void Right(void);
        void Left(void);

        void Render(void) override;
    };


}