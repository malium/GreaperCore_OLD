/***********************************************************************************
*   Copyright 2021 Marcos Sánchez Torrent.                                         *
*   All Rights Reserved.                                                           *
***********************************************************************************/

#pragma once

#ifndef CORE_INTERFACE_H
#define CORE_INTERFACE_H 1

#include "Uuid.h"

namespace greaper
{
	class IGreaperLibrary;

	class IInterface
	{
	public:
		virtual ~IInterface()noexcept = default;

		static constexpr Uuid InterfaceUUID = Uuid{ 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF };
		static constexpr StringView InterfaceName = StringView{ "IInterface" };

		virtual const Uuid& GetInterfaceUUID()const = 0;
		virtual const StringView& GetInterfaceName()const = 0;
		virtual IGreaperLibrary* GetLibrary()const = 0;
	};
}

#endif /* CORE_INTERFACE_H */