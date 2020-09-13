#pragma once

#include <__swn_display_renderer.h>

#define CONSOLE_RENDERER_COUNT_LINES 7

namespace swn
{
    enum ConcoleRenderer_enum : int8_t
    {
        endl = 0,
        upd
    };
    class ConcoleRenderer : public DisplayRenderer
    {
    private:
        String _strlist[CONSOLE_RENDERER_COUNT_LINES];
        size_t _offset;
        int8_t _float_rezolution;

    public:
        ConcoleRenderer();
        ~ConcoleRenderer() override;

        void Add(const String& str);
        void Add(const char& s);
        void Endl(void);
        void ClearLine(void);
        void Clear(void);

        const int8_t& GetFloatResolution(void) const;
        void SetFloatResolution(const int8_t& float_resolution);

        ConcoleRenderer& operator << (const ConcoleRenderer_enum& str);
        ConcoleRenderer& operator << (const String& str);
        ConcoleRenderer& operator << (const char& str);
        ConcoleRenderer& operator << (const int8_t& str);
        ConcoleRenderer& operator << (const int16_t& str);
        ConcoleRenderer& operator << (const int32_t& str);
        ConcoleRenderer& operator << (const uint8_t& str);
        ConcoleRenderer& operator << (const uint16_t& str);
        ConcoleRenderer& operator << (const uint32_t& str);
        ConcoleRenderer& operator << (const unsigned long& str);
        ConcoleRenderer& operator << (const float& str);
        ConcoleRenderer& operator << (const double& str);

        void Render(void) override;
    };

}
   

