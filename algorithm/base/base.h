// =====================================================================================
// 
//    @filename    :  base.h
// 
//    @description :  基本数据类型定义
// 
// -------------------------------------------------------------------------------------
//    @version     :  1.0
//    @created     :  2013年11月12日 16时35分42秒
//    @revision    :  none
//    @compiler    :  g++
// 
//    @author      :  Lei Yunfei (leiyunfei), yunfei_lei@126.com
//    @Company     :  
// 
// =====================================================================================

#ifndef  H_BASE_H_
#define  H_BASE_H_

#if !defined(WIN32)
#   include <stdint.h>
#   include <stddef.h>
#	include <sys/types.h>
#	include <unistd.h>
#else
#	include <windows.h>
#endif

#ifndef TRUE
#	define TRUE	1
#endif

#ifndef FALSE
#	define FALSE 0
#endif

#if !defined(WIN32)
	typedef __int64_t	int64;
	typedef	__int32_t	int32;
	typedef	__int16_t	int16;
	typedef __int8_t	int8;
	typedef __uint64_t	uint64;
	typedef __uint32_t	uint32;
	typedef __uint16_t	uint16;
	typedef __uint8_t	uint8;
#else
	typedef int64_t		int64;
	typedef int32_t		int32;
	typedef int16_t		int16;
	typedef int8_t		int8;
	typedef uint64_t	uint64;
	typedef uint32_t	uint32;
	typedef uint16_t	uint16;
	typedef uint8_t		uint8;
#endif

typedef unsigned char 	byte;
typedef intptr_t        intptr;
typedef uintptr_t       uintptr;

#endif   // ----- #ifndef H_BASE_H_  -----
