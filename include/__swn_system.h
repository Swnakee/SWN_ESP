#pragma once

#include <Arduino.h>
#include <functional>

#include <__swn_event.h>

namespace swn
{
    class ConcoleRenderer;

    class StringEventArgs : public EventArgs
    {
    private:
        const String _str;
    public:
        StringEventArgs(const String& str);
        ~StringEventArgs() override;

        const String& GetString(void) const noexcept;
    };



    class TimeInfo
    {
    private:
        unsigned long _micros;
        float _time;

        unsigned long _micros_counter;
        float _time_max;
        float _time_min;
        float _buffer_time_max;
        float _buffer_time_min;
        int16_t _counter;
        int16_t _max_counter;
    public:
        TimeInfo();
        TimeInfo(const unsigned long& mil, const float& time);
        TimeInfo(const TimeInfo& info);
        TimeInfo& operator = (const TimeInfo& info);

        void FirstUpdate(void);
        void Update(void);

        const int16_t& GetCounter(void) const;
        const int16_t& GetMaxCounter(void) const;
        void SetMaxCounter(const int16_t& new_max_counter);
        const float& GetDeltaTime(void) const;
        const float& GetTimeMax(void) const;
        const float& GetTimeMin(void) const;
    };
    
    class SysObject
    {
    private:
        bool _is_delete; 
    public:
        SysObject();
        virtual ~SysObject();
        virtual void Start() {};
        virtual void FirstUpdate(const TimeInfo& time) {};
        virtual void Update(const TimeInfo& time) {};
        virtual void LastUpdate(const TimeInfo& time) {};
        virtual const char* TypeName(void) {return "NoneType";};

        void Delete(void);
        const bool& IsDelete(void) const;

    };

    class System
    {
    public:
    
    private:
        static std::vector<SysObject*> _sys_obj;
        static EventManger _event_create_obj;
        static EventManger _event_delete_obj;
        static TimeInfo _time_info;
        
    public:
        static void Init(void);
        
        template<typename __type__, typename ... __args__> static __type__* CreateObj(__args__ ... arg)
        {
            __type__* buffer_ptr = new __type__(arg ...);
            _sys_obj.push_back(buffer_ptr);
            _event_create_obj(StringEventArgs(buffer_ptr->TypeName()));
            buffer_ptr->Start();
            return buffer_ptr;
        }

        static void Update();

        static std::vector<SysObject*>& GetSysObject(void);
        static const TimeInfo& GetTimeInfo(void);
        static void SetTimerUpdate(const unsigned long& new_ms);

        static const bool AddEventCreateObj(const pair<String, Event>& func);
        static const bool AddEventDeleteObj(const pair<String, Event>& func);
        static const bool DeleteEventCreateObj(const String& name);
        static const bool DeleteEventDeleteObj(const String& name);
        static void DeleteAllEventCreateObj(void);
        static void DeleteAllEventDeleteObj(void);

    };


    typedef System sys;
    typedef SysObject obj;
}