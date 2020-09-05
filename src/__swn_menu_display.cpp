#include <__swn_menu_display.h>


using namespace std;
using namespace swn;

MenuSwitcher::MenuSwitcher(DisplaySSD1306 *_display) : _display{nullptr}, _offset{0}{}

void MenuSwitcher::__update_menu()
{
    if(_display) _display->SetDisplayRenderer(_menu[_offset].second);
}

DisplaySSD1306* MenuSwitcher::GetDisplay(void)
{
    return _display;
}
void MenuSwitcher::SetDisplay(DisplaySSD1306 *new_display)
{
    _display = new_display;
}


const bool MenuSwitcher::AddMenu(const String& name, DisplayRenderer* ptr)
{
    for(size_t i = 0; i < _menu.size(); i++)
        if(_menu[i].first == name)
            return false;
    _menu.push_back({name, ptr});
    if(_menu.size() == 1) __update_menu(); 
    return true;   
}
DisplayRenderer* MenuSwitcher::GetMeny(const String& name)
{
    for(size_t i = 0; i < _menu.size(); i++)
        if(_menu[i].first == name)
        {
            return _menu[i].second;
        }
    return nullptr;      
}
const bool MenuSwitcher::DeleteMenu(const String& name)
{
    for(size_t i = 0; i < _menu.size(); i++)
        if(_menu[i].first == name)
        {
            _menu.erase(_menu.begin() + i);
            return true;
        }
    return false;    
}

const bool MenuSwitcher::SwitchTo(const String& name)
{
    for(size_t i = 0; i < _menu.size(); i++)
        if(_menu[i].first == name)
        {
            _offset = i;
            __update_menu();
            return true;
        }
    return false;
}
void MenuSwitcher::Right(void)
{
    if(_menu.empty()) return;

    _offset = (_offset+1) % _menu.size();

    __update_menu();
}
void MenuSwitcher::Left(void)
{
    if(_menu.empty()) return;

    if(_offset == 0) _offset = _menu.size() - 1;
    else _offset--;

    __update_menu();
}