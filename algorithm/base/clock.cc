// =====================================================================================
// 
//    @filename    :  clock.cc
// 
//    @description :  时钟类
// 
//    @version     :  1.0
//    @created     :  2013年10月11日 18时21分16秒
//    @revision    :  none
//    @compiler    :  g++
// 
//    @author      :  Lei Yunfei (leiyunfei), yunfei_lei@126.com
//    @company     :  
// 
// =====================================================================================

#include <time.h>

#ifdef LINUX
#	include <sys/time.h>
#else
#	include <sys/timeb.h>
#endif

#include "clock.h"

// 返回当前系统时间，以毫秒为单位
unsigned long long Clock::now()
{
#ifdef LINUX
	timeval tv;
	::gettimeofday(&tv, 0);
	return 1000000LL * tv.tv_sec + tv.tv_usec;
#else
	struct timeb tb;
	::ftime(&tb);
	return 1000000LL * static_cast<unsigned int>(tb.time) + tb.millitm;
#endif
}

Clock::Clock() : _start(0), _elapsed(0), _active(false)
{

}

Clock::~Clock()
{

}

// 返回从开始计时到现在已经流逝的时间，单位为毫秒
// 如果服务器系统时间还未激活，那么就返回上次流逝时间
int Clock::elapsed() const
{
	if (!active()) return _elapsed;
	return static_cast<int>(now() - _start);
}

unsigned int Clock::start()
{
	_active = true;
	_start  = now();
	return _start; 
}

// 停止时钟
// 返回已经流逝的时间（毫秒）
int Clock::stop()
{
	_elapsed = elapsed();
	_active  = false;
	return _elapsed;
}
