#pragma once

#include <__swn_display_renderer.h>

#define GRAPH_X 128
#define GRAPH_Y 64

namespace swn
{

    class Graph : public DisplayRenderer
    {
    protected:
        float _max;
        float _min;

        std::vector<float> _buffer;
        size_t _index_write;
    public:
        Graph(const size_t& buffer_size, const float& min, const float& max);
        ~Graph() override;

        void Add(const float& val);
        
        const float& GetMax(void) const noexcept;
        const float& GetMin(void) const noexcept;
        void SetMax(const float& max);
        void SetMin(const float& min);

        void Render(void) override;

    };

}
   

