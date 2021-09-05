/***********************************************************************************
*   Copyright 2021 Marcos Sánchez Torrent.                                         *
*   All Rights Reserved.                                                           *
***********************************************************************************/

#pragma once

#ifndef CORE_PREREQUISITES_H
#define CORE_PREREQUISITES_H 1

#include "PHAL.h"
#include <chrono>

namespace greaper
{
	using Timepoint_t = std::chrono::high_resolution_clock::time_point;
	
	// fwd
	class IApplication;
	class ILogManager;
	class ILibrary;
	class IGreaperLibrary;


	// types
	using Half = int16;

	using ReflectedFieldID_t = int16;
	using ReflectedTypeID_t = int64;
	using ReflectedSize_t = int64;


	// Reflection ID
	enum CoreReflectedTypeID : ReflectedTypeID_t
	{
		// Base types
		RTI_Bool = 1,
		RTI_Int8,
		RTI_Uint8,
		RTI_Int16,
		RTI_Uint16,
		RTI_Int32,
		RTI_Uint32,
		RTI_Int64,
		RTI_Uint64,
		RTI_Float,
		RTI_Double,
		RTI_Half,

		// Base Containers
		RTI_String = 25,
		RTI_WString,
		RTI_Array,
		RTI_Vector,
		RTI_List,
		RTI_Deque,
		RTI_Map,
		RTI_UnorderedMap,
		RTI_MultiMap,
		RTI_UnorderedMultiMap,
		RTI_Pair,
		RTI_Set,
		RTI_UnorderedSet,
		RTI_MultiSet,
		RTI_UnorderedMultiSet,

		// Classes
		RTI_UUID = 50,
		RTI_Property,

	};
}

#endif /* CORE_PREREQUISITES_H */