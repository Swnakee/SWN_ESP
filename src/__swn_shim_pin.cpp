#include <__swn_shim_pin.h>


using namespace swn;

ShimPin::ShimPin(const int8_t& ledChanel, const int& Hz, const int8_t& resolution) 
    : _ledChannel{ledChanel}, _Hz{Hz}, _resolution{resolution}
{
    ledcSetup(_ledChannel, _Hz, _resolution);
}

ShimPin::ShimPin(const int8_t& pin, const int8_t& ledChanel, const int& Hz, const int8_t& resolution) 
    : ShimPin(ledChanel, Hz, resolution)
{
    pinMode(pin, OUTPUT);
    AttachPin(pin);
}


void ShimPin::Reinit(const int8_t& ledChanel, const int& Hz, const int8_t& resolution) 
{
    _ledChannel = ledChanel;
    _Hz = Hz;
    _resolution = resolution;
    ledcSetup(_ledChannel, _Hz, _resolution);
}
void ShimPin::Reinit( const int& Hz, const int8_t& resolution) 
{
    _Hz = Hz;
    _resolution = resolution;
    ledcSetup(_ledChannel, _Hz, _resolution);
}
void ShimPin::Reinit(const int& Hz) 
{
    _Hz = Hz;
    ledcSetup(_ledChannel, _Hz, _resolution);
}


void ShimPin::AttachPin(const int8_t& pin)
{
    ledcAttachPin(pin, _ledChannel);
}
void ShimPin::DettachPin(const int8_t& pin)
{
    ledcDetachPin(pin);
}

void ShimPin::Write(const int32_t& val)
{
    ledcWrite(_ledChannel, val);
}
const int32_t ShimPin::Read()
{
    return ledcRead(_ledChannel);
}



const int8_t& ShimPin::GetLedChanel(void) const {return _ledChannel;}
const int& ShimPin::GetHz(void) const {return _Hz;}
const int8_t& ShimPin::GetResolution(void) const {return _resolution;}