/***********************************************************************************
*   Copyright 2021 Marcos Sánchez Torrent.                                         *
*   All Rights Reserved.                                                           *
***********************************************************************************/

#pragma once

#ifndef CORE_GREAPER_LIBRARY_H
#define CORE_GREAPER_LIBRARY_H 1

#include "Library.h"
#include "Uuid.h"

namespace greaper
{
	class IApplication;

	class IGreaperLibrary
	{
	public:
		static constexpr Uuid LibraryUUID = Uuid{ 0x10001000, 0x10001000, 0x10001000, 0x10001000 };
		static constexpr StringView LibraryName = StringView{ "Greaper Library" };

		virtual void InitLibrary(IApplication* app) = 0;

		virtual void DeinitLibrary() = 0;

		virtual const Uuid& GetLibraryUuid()const = 0;

		virtual const StringView& GetLibraryName()const = 0;

		virtual IApplication* GetApplication()const = 0;

		virtual Library* GetLibrary()const = 0;
	};
}

#endif /* CORE_GREAPER_LIBRARY_H */