/***********************************************************************************
*   Copyright 2021 Marcos Sánchez Torrent.                                         *
*   All Rights Reserved.                                                           *
***********************************************************************************/

#pragma once

#ifndef CORE_APPLICATION_H
#define CORE_APPLICATION_H 1

#include "Interface.h"

namespace greaper
{
	template<class... Args>
	class Event;

	class IApplication : public IInterface
	{
	public:
		static constexpr Uuid InterfaceUUID = Uuid{ 0xF79C882D, 0x506B4307, 0xBE036194, 0x9F58B3BC };
		static constexpr StringView InterfaceName = StringView{ "Application" };
		
		using OnCloseEvent_t = Event<void>;

		virtual ~IApplication()noexcept = default;

		virtual const Uuid& GetInterfaceUUID()const = 0;

		virtual const StringView& GetInterfaceName()const = 0;

		virtual IGreaperLibrary* GetLibrary()const = 0;

		virtual bool RegisterGreaperLibrary(const WString& libName) = 0;

		virtual bool GetGreaperLibrary(const WStringView& libraryName, IGreaperLibrary** library) = 0;

		virtual bool GetGreaperLibrary(const Uuid& libraryUUID, IGreaperLibrary** library) = 0;

		virtual bool UnregisterGreaperLibrary(IGreaperLibrary* library) = 0;

		virtual bool RegisterInterface(IInterface* interface) = 0;

		virtual bool UnregisterInterface(IInterface* interface) = 0;

		virtual void MakeInterfaceDefault(IInterface* interface) = 0;

		virtual bool GetInterface(const Uuid& interfaceUUID, IInterface** interface)const = 0;

		virtual bool GetInterface(const StringView& interfaceName, IInterface** interface)const = 0;

		virtual bool GetInterface(const Uuid& interfaceUUID, const Uuid& libraryUUID, IInterface** interface)const = 0;

		virtual bool GetInterface(const StringView& interfaceName, const StringView& libraryName, IInterface** interface)const = 0;

		virtual bool GetInterface(const Uuid& interfaceUUID, const StringView& libraryName, IInterface** interface)const = 0;

		virtual bool GetInterface(const StringView& interfaceName, const Uuid& libraryUUID, IInterface** interface)const = 0;

		virtual ILogManager* GetLog()const = 0;

		virtual Timepoint_t GetStartTime()const = 0;

		virtual Timepoint_t GetCurrentTime()const = 0;

		virtual Timepoint_t GetLastUpdateTime()const = 0;

		virtual void SetMaxUpdtesPerSecond(int maxUPS) = 0;

		virtual int GetMaxUpdatesPerSeconds()const = 0;

		virtual double GetUpdateDeltaTime()const = 0;

		virtual void Update() = 0;

		virtual void StopApplication() = 0;

		virtual OnCloseEvent_t* GetOnCloseEvent()const = 0;

		virtual const StringView& GetApplicationName()const = 0;

		virtual int32 GetApplicationVersion()const = 0;

		virtual int32 GetGreaperVersion()const = 0;
		
		virtual const StringView& GetCompilationInfo()const = 0;
	};
}

#endif /* CORE_APPLICATION_H */
