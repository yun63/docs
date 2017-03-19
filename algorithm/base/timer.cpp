/// =====================================================================================
/// 
///    @filename         :  timer.cpp
/// 
///    @description      :  
/// 
///    @version          :  1.0
///    @created          :  2014年01月18日 02时03分12秒
///    @revision         :  none
///    @compiler         :  g++
/// 
///    @author           :  Lei Yunfei (leiyunfei), yunfei_lei@126.com
///    @company          :  
/// 
/// =====================================================================================
#include "timer.h"

Timer::Timer()
{

}

Timer::~Timer()
{
    reset();
}

void Timer::set(gs::GSTime time)
{
    set(time, new TimerEvent());
}

void Timer::set(gs::GSTime time, uint32 variation)
{
    set(time, new TimerEvent(), variation);
}

void Timer::set(gs::GSTime time, TimerEvent *event)
{
    if (event == NULL) return;
    if (_event != NULL) _event->clear();
    _event = event;
    event->set(this, time, variation);
}

void Timer:SetRemaining(gs::GSTime time)
{
    set(TickEventHandler::GetGameTick() + time);
}

void Timer::SetRemaining(gs::GSTime time, uint32 variation)
{
    set(TickEventHandler::GetGameTick() + time, variation);
}

void Timer::SetRemaining(gs::GSTime time, TimerEvent *event)
{
    if (event)
    {
        set(TickEventHandler::GetGameTick() + time, event);
    }
}

void Timer::SetRemaining(gs::GSTime time, TimerEvent *event, uint32 variation)
{
    if (event)
    {
        set(TickEventHandler::GetGameTick() + time, event, variation);
    }

}

void CTimer::reset()
{
    if (_event == NULL) return;
    _event->clear();
    _event = NULL;
}

gs::GSTime CTimer::GetTime() const
{
    if (!is_active()) return 0;
    return _event->GetTime();
}

gs::GSTime CTimer::GetTimeRemaining() const
{
    if (!is_active()) return 0;
    return GetTime() - TickEventHandler::GetGameTick();
}

TimerEvent *Timer::GetEvent()
{
    return _event;
}


/// TimerEvent 实现
TimerEvent::TimerEvent() : _owner(NULL), _time(0)
{

}

TimerEvent::~TimerEvent()
{

}

void TimerEvent::set(Timer *owner, gs::GSTime time)
{
 // TODO:2014年01月20日 00时21分51秒:leiyunfei: 添加异常处理实现并log
//    GS_ASSERT(owner == NULL, "Impossible to set a timer with a NULL owner", return);
    _owner = owner;
    _time  = time;
    TimerManager::GetTimerMgr()->GetEventContainer(time).push_back(this);
}

void TimerEvent::set(Timer *owner,gs::GSTime time, uint32 variation)
{
    GS_ASSERT(owner == NULL, "Impossible to set a timer with a NULL owner", return);
    GS_ASSERT(variation == 0, "shouldn't call this method with variation value of 0", set(owner, time));
    GS_ASSERT(variation > 256, "shouldn't call this method with variation value of > 256", variation = 256);
    GS_ASSERT(_owner != NULL && _owner != owner, "Attemp to change owner of an active event", _owner = owner);

    TimerManager *timer_manager = TimerManager::GetTimerMgr();
    TimerManager::__Vec_event *best = NULL;
    uint32 bestlen = ~0u;

    for (uint32 i = 0; i < variation; ++i)
    {
        TimerManager::__Vec_event &vec = timer_manager->GetEventContainer(time + i);
        uint32 length = static_cast<uint32>(vec.size());
        if (length <= bestlen)
        {
            bestlen = length;
            best = &vec;
            _time = time + i;
        }
    }

    GS_ASSERT(best == NULL, "BUG: Please review timer implementation!", return);
    best->push_back(this);
}
