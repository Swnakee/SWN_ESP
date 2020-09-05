#include <__swn_pin.h>

using namespace swn;


Pin::Pin(const int8_t & pin) : _pin{pin}, _is_enable{false}
{
    pinMode(_pin, OUTPUT);
}
Pin::~Pin() { Disable(); }

void Pin::IsEnable(const bool& flag)
{
    _is_enable = flag;
    digitalWrite(_pin, _is_enable);
}
void Pin::Enable(void)
{
    IsEnable(true);
}
void Pin::Disable(void)
{
    IsEnable(false);
}
void Pin::Invert(void)
{
    IsEnable(!_is_enable);
}

const int8_t& Pin::GetPin(void) const { return _pin; }
const bool& Pin::IsEnable(void) const { return _is_enable; }