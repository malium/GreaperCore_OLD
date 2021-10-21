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
	struct EmptyConfig {  };
	/**
	 * @brief Base class of all manager and factories
	 * 
	 * All interfaces must have a link to their GreaperLibrary.
	 * De/Initialize is called when the interface is just created, as 
	 * constructors/destructors won't be used, but they will be called.
	 * De/Activate is called once the interface is maked the default of its type,
	 * we are planning a way to migrate the resources from the previous interface
	 * of its type to the one is getting activated, so we will be able to switch
	 * interfaces at runtime, allowing to switch to another rendering engine for 
	 * example.
	 * All interfaces will receive the Pre/Post/Fixed/Update event calls, and
	 * IApplication is the resposible to trigger those as also the responsible 
	 * to manage the interfaces.
	 */
	class IInterface
	{
	public:
		virtual ~IInterface()noexcept = default;

		static constexpr Uuid InterfaceUUID = Uuid{  };
		static constexpr StringView InterfaceName = StringView{ "INullInterface" };

		virtual const Uuid& GetInterfaceUUID()const = 0;
		
		virtual const StringView& GetInterfaceName()const = 0;
		
		virtual IGreaperLibrary* GetLibrary()const = 0;

		virtual void Initialize() = 0;

		virtual void Deinitialize() = 0;

		virtual void OnActivate() = 0;

		virtual void OnDeactivate() = 0;

		virtual bool IsActive()const = 0;
		
		virtual bool IsInitialized()const = 0;

		virtual void PreUpdate() = 0;

		virtual void Update() = 0;

		virtual void PostUpdate() = 0;

		virtual void FixedUpdate() = 0;
	};

	template<class InterfaceClass, class InterfaceConfig = EmptyConfig>
	class TInterface : public IInterface
	{
	public:
		virtual ~TInterface()noexcept = default;

		virtual void SetConfig(InterfaceConfig config) = 0;

		virtual const InterfaceConfig& GetConfig()const = 0;

		virtual void OnChangingDefault(InterfaceClass* newDefault) = 0;
	};

	template<class T>
	struct IsInterface
	{
		static constexpr bool value = std::is_base_of_v<IInterface, T>;
	};
	template<class T>
	struct ValidInterface
	{
		static_assert(IsInterface<T>::value, "Trying to validate an Interface that does not derive from IInterface.");
		static constexpr bool UUIDValid = T::InterfaceUUID != IInterface::InterfaceUUID;
		static constexpr bool NameValid = T::InterfaceName != IInterface::InterfaceName;

		static constexpr bool Valid = UUIDValid && NameValid;
	};
}

#endif /* CORE_INTERFACE_H */