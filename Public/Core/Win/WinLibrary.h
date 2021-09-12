/***********************************************************************************
*   Copyright 2021 Marcos Sánchez Torrent.                                         *
*   All Rights Reserved.                                                           *
***********************************************************************************/

#pragma once

#ifndef CORE_WIN_LIBRARY_H
#define CORE_WIN_LIBRARY_H 1

#include "PHAL.h"
#include "MinWinHeader.h"

namespace greaper
{
	class WinLibrary
	{
	public:
		using LibraryHandle = HMODULE;
		static LibraryHandle Load(const wchar* libraryName)
		{
			return LoadLibraryW(libraryName);
		}

		static void Unload(LibraryHandle handle)
		{
			FreeLibrary(handle);
		}

		static FARPROC FuncLoad(LibraryHandle handle, const achar* procName)
		{
			FARPROC proc = nullptr;
			*(void**)(&proc) = GetProcAddress(handle, procName);
			return proc;
		}
	};
	using OSLibrary = WinLibrary;
}

#endif /* CORE_IWINLIBRARY_H */
