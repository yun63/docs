/// =====================================================================================
/// 
///    @filename         :  timer.h
/// 
///    @description      :  完整定时器系统. 
///                         当调用用户类的set()或者SetRemaining()方法被调用时,
///                         用户类注册的回调函数在指定的时间内将会激活;如果Timer对象销毁后,
///                         它注册的回调函数会自动取消. 每个tick必须调用TimerManager:TickUpdate()方法.
/// 
/// -------------------------------------------------------------------------------------
///    @version          :  1.0
///    @created          :  2014年01月01日 21时37分58秒
///    @revision         :  none
///    @compiler         :  g++
/// 
///    @author           :  Lei Yunfei (leiyunfei), yunfei_lei@126.com
///    @Company          :  
/// 
/// =====================================================================================

/*  Example 1: class containing a timer object
    class MyClass
    {
         public:
             void StartTimer() 
             {
                 // set the timer to trigger in 50 ticks
                 _timer.SetRemaining(50);
             }
             void update()
             {
                 if (_timer.IsActive())
                 {
                     nlinfo("time remaining: ",_timer.GetTimeRemainig());
                 }
                 else
                 {
                     // set the timer to trigger 20 ticks
                     _timer.SetRemaining(20);
                 }
             }
         private:
             Timer _timer;
    };

    Example 2: class using a timer and a custom event handler to trigger regular actions
    -------------
    class MyClass;
    class MyTimerEvent;

    class MyTimerEvent : public TimerEvent
    {
         public:
             MyTimerEvent(MyClass *parent);
             void TimerCallback(Timer *owner);
         private:
             MyClass *_parent;
    };

    class MyClass
    {
         public:
             void StartTimer()
             {
                 // set timer to trigger in 50 ticks
                 _timer.SetRemaining(50, new MyTimerEvent(this));
             }
             void DoSomething(TimerEvent *event)
             {
                 nlinfo("hello, world");
                 // set the timer to trigger in 20 ticks with the same event handler
                 _timer.SetRemaining(20, event);
             }
         private:
             Timer _timer;
    };

    void MyTimerEvent::MyTimerEvent(MyClass *parent)
    {
         _parent = parent;
    }

    void MyTimerEvent::TimerCallback(Timer *owner)
    {
         _parent->dosomething(this);
    }
*/


#ifndef  __TIMER_H_
#define  __TIMER_H_

#include <vector>

#include "types.h"
#include "time.h"

class Timer;
class TimerEvent;
class TimerManager;


/// ================================================================
///  @class : Timer
///  @description :  通用定时器类定义
/// ================================================================
class Timer
{
    public:
        Timer();      
        virtual ~Timer();

        /**
         * @brief  set 设置定时timer并且清除用户事件对象
         * @param  time
         */
        void set(gs::GSTime time);
        /**
         * @brief  set 设置某时间段timer并且清除用户事件对象
         * @param  time
         * @param  duration
         */
        void set(gs::GSTime time, uint32 duration);
        /**
         * @brief  set 设置定长时间timer并且绑定事件处理对象
         * @param  time timer触发时间
         * @param  event 事件处理对象
         */
        void set(gs::GSTime time, TimerEvent *event);
        /**
         * @brief  set 设置某时间段timer并且绑定事件处理对象
         * @param  time
         * @param  event
         * @param  duration
         */
        void set(gs::GSTime time, TimerEvent *event, uint32 duration);

        /**
         * @brief  SetRemaining 设置timer(now + time)并且清除用户事件对象
         * @param  time
         */
        void SetRemaining(gs::GSTime time);
        /**
         * @brief  SetRemaining 设置(now + time) ~ (now + time + duration)timer并且清除用户事件对象
         * @param  time
         * @param  duration
         */
        void SetRemaining(gs::GSTime time, uint32 duration);
        /**
         * @brief  SetRemaining 设置timer(now + time),绑定timer事件处理对象
         * @param  time
         * @param  event
         */
        void SetRemaining(gs::GSTime time, TimerEvent *event);
        /**
         * @brief  SetRemaining 
         * @param  time
         * @param  event
         * @param  duration
         */
        void SetRemaining(gs::GSTime time, TimerEvent *event, uint32 duration);
        /**
         * @brief  is_active timer是否激活
         * @return  
         */
        bool is_active() const;
        /**
         * @brief  reset 重置timer并且清理timer事件
         */
        void reset();
        /**
         * @brief  GetTime 获取timer目标时间,如果没有激活事件返回0
         * @return  
         */
        gs::GSTime GetTime() const;
        /**
         * @brief  GetTimeRemaining 获取timer剩余时间,如果没有激活事件返回0
         * @return  
         */
        gs::GSTime GetTimeRemaining() const;
        /**
         * @brief  GetEvent 获取当前事件对象的指针
         * @return  
         */
        TimerEvent *GetEvent();


    protected:

    private:
        /**
         * timer禁止拷贝&赋值
         */
        Timer(const Timer &);
        Timer &operator = (const Timer &);

        gs::SmartPtr<TimerEvent> _event;

};  // ---- end of class Timer   ----


/// ================================================================
///  @class : TimerEvent
///  @description :  定时器事件类
/// ================================================================
class TimerEvent : public gs::RefCount
{
    public:
        friend class Timer;
        frient class TimerManager;

        TimerEvent();
        virtual ~TimerEvent();

        virtual void TimerCallback(Timer *owner) {}
        gs::GSTime GetTime() const;
        Timer *GetOwner() const;

        bool is_active() const;

    private:
        void set(Timer *owner, gs::GSTime time);
        void set(Timer *owner, gs::GSTime, uint32 variation);
        void clear();
        void process_event();

    private:
        gs::GSTime _time;
        Timer *_owner;
};  // ---- end of class TimerEvent   ----

class TimerManager : public ServieceSingleton
{
    public:
        friend class TimerEvent;

        static TimerManager *GetTimerMgr();

        void void tickupdate();
        /**
         * @brief  synctick 当tick服务连接后回调,用来同步事件对象的tick时间值
         */
        void synctick();

    private:
        TimerManager();

        typedef std::vector< gs::SmartPtr<TimerEvent> > __Vec_event;

        __Vec_event &GetEventContainer(gs::GSTime time);

    private:
        gs::GSTime _lasttick;
        __Vec_event _event_vectors[256];
};



#endif   // ----- #ifndef __TIMER_H_ -----


