#include <__swn_menu_display.h>


using namespace std;
using namespace swn;

MenuSwitcher::MenuSwitcher() : DisplayRenderer(), _menu(), _offset{0}, _is_init_menu{false} {}

MenuSwitcher::~MenuSwitcher() {}


const bool MenuSwitcher::AddRenderer(const String& name, DisplayRenderer* ptr)
{
    for(size_t i = 0; i < _menu.size(); i++)
        if(_menu[i].first == name)
            return false;

    _menu.push_back({name, ptr});

    return true;
}

DisplayRenderer* MenuSwitcher::GetRenderer(const String& name)
{
    for(size_t i = 0; i < _menu.size(); i++)
        if(_menu[i].first == name)
            return _menu[i].second;
    return nullptr;
}

String MenuSwitcher::GetActiveRendrerName(void) const noexcept
{
    return _menu[_offset].first;
}

DisplayRenderer* MenuSwitcher::GetActiveRendrer(void) const noexcept
{
    return _menu[_offset].second;
}

const bool MenuSwitcher::DeleteRenderer(const String& name)
{
    if(_menu.empty()) return false;

    String active_name = GetActiveRendrerName();
    bool flag = active_name != name && !active_name.isEmpty();

    for(size_t i = 0; i < _menu.size(); i++)
        if(_menu[i].first == name)
        {
            _menu.erase(_menu.begin() + i);
            if(flag) SwitchTo(active_name);
            else _is_init_menu = false;
            return true;
        }
    return false;
}

void MenuSwitcher::DeleteAllRenderer(void)
{
    _menu.clear();
    _is_init_menu = false;
}


const bool MenuSwitcher::SwitchTo(const String& name)
{
    for(size_t i = 0; i < _menu.size(); i++)
        if(_menu[i].first == name)
        {
            _offset = i;
            return _is_init_menu = true;
        }
    return _is_init_menu = false;
}
void MenuSwitcher::Right(void)
{
    _offset = (_offset+1)%_menu.size();
}
void MenuSwitcher::Left(void)
{
    if(_offset == 0) _offset = _menu.size() - 1;
    else _offset--;
}

void MenuSwitcher::Render(void)
{
    if(!_is_init_menu)
    {
        DisplayRenderer::Render();
    }
    else if(GetDisplay())
    {
        _menu[_offset].second->Render();
    }
}




