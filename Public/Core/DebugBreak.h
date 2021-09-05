/***********************************************************************************
*   Copyright 2021 Marcos Sánchez Torrent.                                         *
*   All Rights Reserved.                                                           *
***********************************************************************************/

#pragma once

#ifndef GREAPER_CORE_DEBUG_BREAK_H
#define GREAPER_CORE_DEBUG_BREAK_H

#include "CorePrerequisites.h"
#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#if PLT_WINDOWS
#include "Win/MinWinHeader.h"
#endif

namespace greaper::Impl
{
	void _LogBreak(const achar* msg)
	{
		FILE* file = nullptr;
		
		// TODO: do error log
	}
	INLINE void _TriggerBreak(const achar* message, va_list arglist)
	{
		static GREAPER_THLOCAL achar msg[10240];
		::vsnprintf(msg, ArraySize(msg), message, arglist);

#if PLT_WINDOWS
		constexpr UINT mbType = MB_ICONERROR
#if GREAPER_DEBUG_BREAK
				| MB_ABORTRETRYIGNORE
#else
				| MB_OK
#endif
				| MB_TASKMODAL | MB_TOPMOST;

		const auto retVal = MessageBoxA(nullptr, msg, "Greaper Assertion", mbType);
		
		if (retVal == IDRETRY)
		{
			TRIGGER_BREAKPOINT();
		}
		else if (retVal == IDIGNORE)
		{
			return;
		}
#else
		std::cerr << "Greaper Assertion: " << assertMsg;
#if GREAPER_DEBUG_BREAK
		TRIGGER_BREAKPOINT();
#endif
#endif
		_LogBreak(msg);
		exit(EXIT_FAILURE);
	}
	INLINE void _BreakFmt(const achar* message, ...)
	{
		va_list arglist;
		va_start(arglist, message);
		_TriggerBreak(message, arglist);
		va_end(arglist);
	}
}

#define Break(msg, ...) greaper::Impl::_BreakFmt("STOP! at: " FUNCTION_FULL ", message: " msg, __VA_ARGS__)

#if GREAPER_ENABLE_BREAK
#define Verify(exp, msg, ...) { if(!(exp)) greaper::Impl::_BreakFmt("STOP! exp: " #exp " not verified, at: " FUNCTION_FULL ", message: " msg, __VA_ARGS__); }
#define VerifyNot(exp, msg, ...) { if(!(exp)) greaper::Impl::_BreakFmt("STOP! exp: !" #exp " not verified, at: " FUNCTION_FULL ", message: " msg, __VA_ARGS__); }
#define VerifyInequal(a, b, msg, ...) { if((a) == (b)) greaper::Impl::_BreakFmt("STOP! exp: " #a " != " #b " not verified, at: " FUNCTION_FULL ", message: " msg, __VA_ARGS__); }
#define VerifyEqual(a, b, msg, ...) { if((a) != (b)) greaper::Impl::_BreakFmt("STOP! exp: " #a " == " #b " not verified, at: " FUNCTION_FULL ", message: " msg, __VA_ARGS__); }
#define VerifyGreater(a, b, msg, ...) { if((a) <= (b)) greaper::Impl::_BreakFmt("STOP! exp: " #a " > " #b " not verified, at: " FUNCTION_FULL ", message: " msg, __VA_ARGS__); }
#define VerifyGreaterEqual(a, b, msg, ...) { if((a) < (b)) greaper::Impl::_BreakFmt("STOP! exp: " #a " >= " #b " not verified, at: " FUNCTION_FULL ", message: " msg, __VA_ARGS__); }
#define VerifyLess(a, b, msg, ...) { if((a) >= (b)) greaper::Impl::_BreakFmt("STOP! exp: " #a " < " #b " not verified, at: " FUNCTION_FULL ", message: " msg, __VA_ARGS__); }
#define VerifyLessEqual(a, b, msg, ...) { if((a) > (b)) greaper::Impl::_BreakFmt("STOP! exp: " #a " <= " #b " not verified, at: " FUNCTION_FULL ", message: " msg, __VA_ARGS__); }
#define VerifyNull(ptr, msg, ...) { if((ptr) != nullptr) greaper::Impl::_BreakFmt("STOP! exp: " #ptr " is not nullptr, at: " FUNCTION_FULL ", message: " msg, __VA_ARGS__); }
#define VerifyNotNull(ptr, msg, ...) { if((ptr) == nullptr) greaper::Impl::_BreakFmt("STOP! exp: " #ptr " is nullptr, at: " FUNCTION_FULL ", message: " msg, __VA_ARGS__); }
#define VerifyWithin(value, min, max, msg, ...) { if((value) <= (min)|| (value) >= (max)) greaper::Impl::_BreakFmt("STOP! exp: " #value " not inside of (" #min ", " #max ") range , at: " FUNCTION_FULL ", message: " msg, __VA_ARGS__); }
#define VerifyWithinInclusive(value, min, max, msg, ...) { if((value) < (min) || (value) > (max)) greaper::Impl::_BreakFmt("STOP! exp: " #value " not inside of [" #min ", " #max "] range , at: " FUNCTION_FULL ", message: " msg, __VA_ARGS__); }
#define VerifyNotWithin(value, min, max, msg, ...) { if((value) >= (min) && (value) <= (max)) greaper::Impl::_BreakFmt("STOP! exp: " #value " not outside of (" #min ", " #max ") range , at: " FUNCTION_FULL ", message: " msg, __VA_ARGS__); }
#define VerifyNotWithinInclusive(value, min, max, msg, ...) { if((value) > (min) && (value) < (max)) greaper::Impl::_BreakFmt("STOP! exp: " #value " not outside of [" #min ", " #max "] range , at: " FUNCTION_FULL ", message: " msg, __VA_ARGS__); }
#else
#define Verify(exp, ...) { volatile bool res = (exp); }
#define VerifyNot(exp, ...) { volatile bool res = !(exp); }
#define VerifyInequal(a, b, ...) { volatile bool res = (a) != (b); }
#define VerifyEqual(a, b, ...) { volatile bool res = (a) == (b); }
#define VerifyGreater(a, b, ...) { volatile bool res = (a) > (b); }
#define VerifyGreaterEqual(a, b, ...) { volatile bool res = (a) >= (b); }
#define VerifyLess(a, b, ...) { volatile bool res = (a) < (b); }
#define VerifyLessEqual(a, b, ...) { volatile bool res = (a) <= (b); }
#define VerifyNull(ptr, ...) { volatile bool res = (ptr) == nullptr; }
#define VerifyNotNull(ptr, ...) { volatile bool res = (ptr) != nullptr; }
#define VerifyWithin(val, min, max, ...) { volatile bool res = (value) > (min) && (value) < (max); }
#define VerifyWithinInclusive(val, min, max, ...) { volatile bool res = (value) >= (min) && (value) <= (max); }
#define VerifyNotWithin(val, min, max, ...) { volatile bool res = (value) < (min) && (value) > (max); }
#define VerifyNotWithinInclusive(val, min, max, ...) { volatile bool res = (value) <= (min) && (value) >= (max); }
#endif

#endif /* GREAPER_CORE_DEBUG_BREAK_H */
