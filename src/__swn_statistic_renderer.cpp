#include <__swn_statistic_renderer.h>
#include <esp.h>

using namespace swn;

StatisticRenderer::StatisticRenderer() {}
StatisticRenderer::~StatisticRenderer() {}

void StatisticRenderer::Render(void)
{
    DisplaySSD1306 *dis = GetDisplay();
    if(dis)
    {
        SSD1306 &display_src = dis->GetDisplay();
        static size_t counter = 0;
        counter++;
        display_src.clear();
        uint8_t ofpx = 0;
        display_src.drawString(0,ofpx,"RAM_Size: " + String(ESP.getHeapSize())); ofpx+=9;
        display_src.drawString(0,ofpx,"Free_RAM: " + String(ESP.getFreeHeap())); ofpx+=9;
        display_src.drawString(0,ofpx,String(counter)); ofpx+=9;
        display_src.display();
        
    }
}

void StatisticRenderer::Update(const TimeInfo& time)
{
    Render();   
}


const char* StatisticRenderer::TypeName(void) 
{
    return "StatisticRenderer";
}
