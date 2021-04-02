/***********************************************************************************
*   Copyright 2021 Marcos S�nchez Torrent.                                         *
*   All Rights Reserved.                                                           *
***********************************************************************************/

#pragma once

/**
*	Enables the use of Assertions in the project, even though
*	the Assert(msg) function will still trigger assertions.
*	Assertions done by Assert(msg), will still trigger, use them
*	if you need them even if Assertions are disabled
*/
#ifndef GREAPER_ENABLE_ASSERTIONS
#if GREAPER_FRELEASE
#define GREAPER_ENABLE_ASSERTIONS 0
#else
#define GREAPER_ENABLE_ASSERTIONS 1
#endif
#endif

#ifndef GREAPER_USE_BASIC_TYPEINFO
#define GREAPER_USE_BASIC_TYPEINFO 0
#endif