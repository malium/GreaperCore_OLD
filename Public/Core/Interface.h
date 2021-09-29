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
	class IInterface
	{
	public:
		virtual ~IInterface()noexcept = default;

		static constexpr Uuid InterfaceUUID = Uuid{  };
		static constexpr StringView InterfaceName = StringView{ "INullInterface" };

		virtual const Uuid& GetInterfaceUUID()const = 0;
		
		virtual const StringView& GetInterfaceName()const = 0;
		
		virtual IGreaperLibrary* GetLibrary()const = 0;

		virtual void PreUpdate() = 0;

		virtual void Update() = 0;

		virtual void PostUpdate() = 0;

		virtual void FixedUpdate() = 0;
	};

	template<class T>
	struct ValidInterface
	{
		static_assert(std::is_base_of_v<IInterface, T>, "Trying to validate an Interface that does not derive from IInterface");
		static constexpr bool UUIDValid = T::InterfaceUUID != IInterface::InterfaceUUID;
		static constexpr bool NameValid = T::InterfaceName != IInterface::InterfaceName;

		static constexpr bool Valid = UUIDValid && NameValid;
	};
}

#endif /* CORE_INTERFACE_H */