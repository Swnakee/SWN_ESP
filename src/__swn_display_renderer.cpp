#include <__swn_display_renderer.h>

using namespace std;
using namespace swn;


DisplaySSD1306::DisplaySSD1306(uint8_t _address, uint8_t _sda, uint8_t _scl) : _display(0x3c, 23, 22)
    
{
    _display.init();
    _display.flipScreenVertically();
}

SSD1306* DisplaySSD1306::GetDisplay(void) noexcept
{
    return &_display;
    
}

/////////////////////////////

DisplayRenderer::DisplayRenderer(void) : _display{nullptr}, _sub_render([this](Event*,void*)
{
    this->Render();
})
{}
DisplayRenderer::~DisplayRenderer(){}

void DisplayRenderer::SetDisplay(DisplaySSD1306 *display) noexcept
{
    _display = display;
}
DisplaySSD1306* DisplayRenderer::GetDisplay(void) noexcept
{
    return _display;
}

Subscriber* DisplayRenderer::Sub_Render(void) 
{
    return &_sub_render;
}

void DisplayRenderer::Render(void)
{
    if(_display)
    {
        _display->GetDisplay()->clear();    
        _display->GetDisplay()->drawString(0,0, "Display: nullptr");
        _display->GetDisplay()->display();    
    }
}