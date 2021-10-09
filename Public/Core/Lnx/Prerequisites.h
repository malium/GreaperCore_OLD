/***********************************************************************************
*   Copyright 2021 Marcos Sánchez Torrent.                                         *
*   All Rights Reserved.                                                           *
***********************************************************************************/

#pragma once

#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>

struct LnxTypes : BasicTypes
{
    typedef __SIZE_TYPE__ sizetype;
    typedef __SSIZE_T_TYPE ssizetype;
    typedef __CHAR16_TYPE__ widechar;
};

typedef LnxTypes PlatformTypes;

/* Function type macros */
#define INLINE inline __attribute__ ((always_inline))
#define NOINLINE __attribute__((noinline))
#define FUNCTION_NO_RETURN_START 
#define FUNCTION_NO_RETURN_END __attribute__((noreturn))
#define TRIGGER_BREAKPOINT() __asm__ volatile("int $0x03")

#define DLLIMPORT __attribute__((visibility("default")))
#define DLLEXPORT __attribute__((visibility("default")))

/* String constants */
#ifndef PATH_SEPARATOR
#define PATH_SEPARATOR '/'
#endif
#ifndef PATH_SEPARATOR_WIDE
#define PATH_SEPARATOR_WIDE L'/'
#endif