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

		static LibraryHandle Load(const achar* libraryName)
		{
			return LoadLibraryA(libraryName);
		}

		static LibraryHandle Load(const wchar* libraryName)
		{
			return LoadLibraryW(libraryName);
		}

		static void Unload(LibraryHandle handle)
		{
			FreeLibrary(handle);
		}

		static FuncPtr FuncLoad(LibraryHandle handle, const achar* procName)
		{
			const auto proc = GetProcAddress(handle, procName);
			/*if (proc == nullptr)
				return nullptr;*/
			return reinterpret_cast<FuncPtr>(proc);
		}
	};
	using OSLibrary = WinLibrary;
}

#endif /* CORE_IWINLIBRARY_H */
