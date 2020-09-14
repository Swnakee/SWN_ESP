#include <__swn_graph.h>
#include <math.h>
#include <__swn_console_renderer.h>

using namespace swn;

const size_t __Max(const std::vector<float>& vec)
{
    size_t index = 0;
    for(size_t i = 1; i < vec.size(); i++)
        index = vec[index] < vec[i] ? i : index;
    return index;
}
const size_t __Min(const std::vector<float>& vec)
{
    size_t index = 0;
    for(size_t i = 1; i < vec.size(); i++)
        index = vec[index] > vec[i] ? i : index;
    return index;
}
        
Graph::Graph(const size_t& buffer_size, const float& min, const float& max) : _max{max}, _min{min}, _buffer{}, _index_write{0}
{
    _buffer.resize(buffer_size);
    std::fill(_buffer.begin(), _buffer.end(), _min);
}
Graph::~Graph()
{

}

void Graph::Add(const float& val)
{
    float smooth_val = _buffer[((_index_write-1)%_buffer.size())];
    _buffer[_index_write] = smooth_val*0.5 + val*0.5;
    //_buffer[_index_write] = val;
    _index_write = ((_index_write+1)%_buffer.size());
    //if(_index_write%5 == 0)
    {
        _max = _max * 0.8 + _buffer[__Max(_buffer)] * 2 * 0.2;
        _min = _min * 0.8 + _buffer[__Min(_buffer)] * 0.5f * 0.2; 
        
    }
}

const uint8_t __Get_Y__(const float& buf_y, const float& min, const float& max)
{
    float ret = std::min(std::max(buf_y, min), max) - min;
    ret = (ret / (max-min)) * GRAPH_Y;
    return (GRAPH_Y - ret);
}


const float& Graph::GetMax(void) const noexcept {return _max;}
const float& Graph::GetMin(void) const noexcept {return _min;}
void Graph::SetMax(const float& max) {_max = max;}
void Graph::SetMin(const float& min) {_min = min;}

void Graph::Render(void) 
{
    DisplaySSD1306 *dis = GetDisplay();
    if(dis)
    {
        SSD1306 &display_src = *dis->GetDisplay();
        display_src.clear();
        
        String str_min = String(_min, 6);
        String str_max = String(_max, 6);
        String str_active = String(_buffer[_index_write], 6);
        
        display_src.drawLine(0, 0, 127, 0);
        display_src.drawLine(0, 63, 127, 63);
        const uint8_t vertucal = (GRAPH_X / (float)_buffer.size()) * _index_write;
        display_src.drawLine(vertucal, 0, vertucal, 63);
        {
            uint8_t left_x = 0;
            uint8_t left_y = 0;
            uint8_t right_x = 0;
            uint8_t right_y = 0;
            const float step = GRAPH_X / (float)(_buffer.size()-1);

            left_x = 0;
            left_y = __Get_Y__(_buffer.front(), _min, _max);

            ///////////////
            for(size_t i = 1; i < _buffer.size()-1; i++)
            {
                right_x = i*step;
                right_y = __Get_Y__(_buffer[i], _min, _max);
                display_src.drawLine(left_x, left_y, right_x, right_y);
                left_x = right_x;
                left_y = right_y;
            }
            ///////////////

            right_x = GRAPH_X-1;
            right_y = __Get_Y__(_buffer.back(), _min, _max);
            display_src.drawLine(left_x, left_y, right_x, right_y);
        }

        display_src.drawString(0,0, str_max + " - " + str_active);
        display_src.drawString(0,0, str_max);
        display_src.drawString(0,64-12, str_min);

        display_src.display();
    }
}
