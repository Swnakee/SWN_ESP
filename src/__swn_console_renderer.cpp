#include <__swn_console_renderer.h>
#include <__swn_define.h>

using namespace swn;

#define EMPTY_STRING ""

ConcoleRenderer::ConcoleRenderer() : DisplayRenderer(), _strlist{}, _offset{0}, _float_rezolution{2}
{
    for(size_t i = 0; i < CONSOLE_RENDERER_COUNT_LINES; i++)
        _strlist[i] = EMPTY_STRING;
    _offset = 0;
}

ConcoleRenderer::~ConcoleRenderer() {}

void ConcoleRenderer::Add(const String& str)
{
    _strlist[_offset] += str;
    #ifdef __CONOLE_RENDERER_TO_SERIAL__
    Serial.print(str);
    #endif
}
void ConcoleRenderer::Add(const char& s)
{
    _strlist[_offset] += s;
    #ifdef __CONOLE_RENDERER_TO_SERIAL__
    Serial.print(s);
    #endif
}
void ConcoleRenderer::Endl(void)
{
    _offset = (_offset+1)%CONSOLE_RENDERER_COUNT_LINES;
    _strlist[_offset] = EMPTY_STRING;
    #ifdef __CONOLE_RENDERER_TO_SERIAL__
    Serial.println();
    #endif
}
void ConcoleRenderer::ClearLine(void)
{
    _strlist[_offset] = EMPTY_STRING;
    #ifdef __CONOLE_RENDERER_TO_SERIAL__
    Serial.print('\r');
    #endif
}
void ConcoleRenderer::Clear(void)
{
    for(size_t i = 0; i < CONSOLE_RENDERER_COUNT_LINES; i++)
        _strlist[i] = EMPTY_STRING;
    _offset = 0;
}

const int8_t& ConcoleRenderer::GetFloatResolution(void) const {return _float_rezolution;}
void ConcoleRenderer::SetFloatResolution(const int8_t& float_resolution) { _float_rezolution = float_resolution; }

ConcoleRenderer& ConcoleRenderer::operator << (const ConcoleRenderer_enum& str)
{
    switch (str)
    {
    case ConcoleRenderer_enum::endl: Endl(); break;
    case ConcoleRenderer_enum::upd: Render(); break;
    default: break;
    }
    return *this;   
}
ConcoleRenderer& ConcoleRenderer::operator << (const String& str)
{
    size_t index = 0;
    while(index < str.length())
    {
        bool endl = false;
        String buffer_str;
        for(; index < str.length(); index++)
        {
            if(str[index] == '\n')
            {
                endl = true;
                index++;
                break;
            }
            buffer_str += str[index];
        }
        Add(buffer_str);
        
        if(endl) 
            Endl();
    }
    return *this;
}
ConcoleRenderer& ConcoleRenderer::operator << (const char& s)
{
    if(s == '\n') Endl();
    else Add(s);
    return *this;
}
ConcoleRenderer& ConcoleRenderer::operator << (const int8_t& str)
{
    return *this << String(str);
}
ConcoleRenderer& ConcoleRenderer::operator << (const int16_t& str)
{
    return *this << String(str);
}
ConcoleRenderer& ConcoleRenderer::operator << (const int32_t& str)
{
    return *this << String(str);
}
ConcoleRenderer& ConcoleRenderer::operator << (const uint8_t& str)
{
    return *this << String(str);
}
ConcoleRenderer& ConcoleRenderer::operator << (const uint16_t& str)
{
    return *this << String(str);
}
ConcoleRenderer& ConcoleRenderer::operator << (const uint32_t& str)
{
    return *this << String(str);
}
ConcoleRenderer& ConcoleRenderer::operator << (const unsigned long& str)
{
    return *this << String(str);
}
ConcoleRenderer& ConcoleRenderer::operator << (const float& str)
{
    return *this << String(str, _float_rezolution);
}
ConcoleRenderer& ConcoleRenderer::operator << (const double& str)
{
    return *this << String(str, _float_rezolution);
}


void ConcoleRenderer::Render(void)
{
    DisplaySSD1306 *dis = GetDisplay();
    if(dis)
    {
        SSD1306 &display_src = *dis->GetDisplay();
        
        display_src.clear();
        uint8_t buffer_count = CONSOLE_RENDERER_COUNT_LINES - 1;
        for(size_t i = 0; i < buffer_count; i++)
        {
            display_src.drawString(0,i*9, _strlist[(_offset+i+1)%CONSOLE_RENDERER_COUNT_LINES]);
        }
        display_src.drawString(0,buffer_count*9,">" + _strlist[(_offset+buffer_count+1)%CONSOLE_RENDERER_COUNT_LINES]);
        display_src.display();
    }
}
 

