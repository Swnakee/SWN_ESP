#include "__swn_display_SSD1306.h"

using namespace swn;


DisplaySSD1306::DisplaySSD1306(uint8_t _address, uint8_t _sda, uint8_t _scl) : _display(_address, _sda, _scl), _renderer{nullptr} 
{
    _display.init();
    _display.flipScreenVertically();
}
DisplaySSD1306::~DisplaySSD1306() {}

DisplayRenderer* DisplaySSD1306::GetDisplayRenderer(void)
{
    return _renderer;
}

void DisplaySSD1306::SetDisplayRenderer(DisplayRenderer* rendrer)
{
    if(_renderer) _renderer->SetDisplay(nullptr);
    _renderer = rendrer;
    if(_renderer)
    {
        _renderer->SetDisplay(this);
        _renderer->NeedUpdate();
    }
}

SSD1306& DisplaySSD1306::GetDisplay(void)
{
    return _display;
}

//////////////


DisplayRenderer::DisplayRenderer(void) : _display{nullptr}, _need_update{false}{}
DisplayRenderer::~DisplayRenderer() {}

void DisplayRenderer::SetDisplay(DisplaySSD1306 *display)
{
    _display = display;
}

DisplaySSD1306* DisplayRenderer::GetDisplay(void) noexcept
{
    return _display;
}

void DisplayRenderer::NeedUpdate(const bool& flag) noexcept
{
    _need_update = flag;
}

const bool& DisplayRenderer::GetIsNeedUpdate(void) const noexcept
{
    return _need_update;
}


void DisplayRenderer::Render(void) 
{
    if(_display)
    {
        _display->GetDisplay().drawString(0,0, "DisplayRenderer: nullptr");
        _display->GetDisplay().display();     
    }   
}
 
void DisplayRenderer::Update(const TimeInfo& time)
{
    if(_need_update && _display)
    {
        Render();
        _need_update = false;
    }
}

const char* DisplayRenderer::TypeName(void)
{
    return "DisplayRenderer";
}


