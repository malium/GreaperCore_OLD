/***********************************************************************************
*   Copyright 2021 Marcos Sánchez Torrent.                                         *
*   All Rights Reserved.                                                           *
***********************************************************************************/

#pragma once

#ifndef CORE_I_APPLICATION_H
#define CORE_I_APPLICATION_H 1

#include "Interface.h"
#include "Result.h"

namespace greaper
{
	struct ApplicationConfig
	{
		StringView ApplicationName = "unnamed"sv;
		int32 ApplicationVersion = 0;
		
		uint32 GreaperLibraryCount = 0;
		WStringView* GreaperLibraries = nullptr;
	};

	class IApplication : public TInterface<IApplication, ApplicationConfig>
	{
	public:
		static constexpr Uuid InterfaceUUID = Uuid{ 0xF79C882D, 0x506B4307, 0xBE036194, 0x9F58B3BC };
		static constexpr StringView InterfaceName = "Application"sv;
		
		using OnCloseEvent_t = Event<void>;

		virtual ~IApplication()noexcept = default;

		virtual EmptyResult RegisterGreaperLibrary(IGreaperLibrary* library) = 0;

		virtual Result<IGreaperLibrary*> RegisterGreaperLibrary(const WStringView& libPath) = 0;

		virtual Result<IGreaperLibrary*> GetGreaperLibrary(const StringView& libraryName) = 0;

		virtual Result<IGreaperLibrary*> GetGreaperLibrary(const Uuid& libraryUUID) = 0;

		virtual EmptyResult UnregisterGreaperLibrary(IGreaperLibrary* library) = 0;

		virtual EmptyResult RegisterInterface(IInterface* interface) = 0;

		virtual EmptyResult UnregisterInterface(IInterface* interface) = 0;

		virtual void MakeInterfaceDefault(IInterface* interface) = 0;

		virtual Result<IInterface*> GetInterface(const Uuid& interfaceUUID)const = 0;

		virtual Result<IInterface*> GetInterface(const StringView& interfaceName)const = 0;

		virtual Result<IInterface*> GetInterface(const Uuid& interfaceUUID, const Uuid& libraryUUID)const = 0;

		virtual Result<IInterface*> GetInterface(const StringView& interfaceName, const StringView& libraryName)const = 0;

		virtual Result<IInterface*> GetInterface(const Uuid& interfaceUUID, const StringView& libraryName)const = 0;

		virtual Result<IInterface*> GetInterface(const StringView& interfaceName, const Uuid& libraryUUID)const = 0;

		virtual void StartApplication() = 0;

		virtual bool AppHasToStop()const = 0;

		virtual void StopApplication() = 0;

		virtual OnCloseEvent_t*const GetOnCloseEvent() = 0;

		virtual const StringView& GetApplicationName()const = 0;

		virtual int32 GetApplicationVersion()const = 0;

		virtual int32 GetGreaperVersion()const = 0;
		
		virtual const StringView& GetCompilationInfo()const = 0;

		template<class T>
		Result<T*> RegisterGreaperLibraryT(const WStringView& libPath)
		{
			static_assert(std::is_base_of_v<IGreaperLibrary, T>, "Trying to register a GreaperLibrary "
				"but its implementation doesn't derive from IGreaperLibrary.");
			auto res = RegisterGreaperLibrary(libPath);
			if(res.HasFailed())
				return CopyFailure<T*>(res);
			T* lib = reinterpret_cast<T*>(res.GetValue());
			return CreateResult(lib);
		}

		template<class T>
		Result<T*> GetGreaperLibraryT(const StringView& libraryName)
		{
			static_assert(std::is_base_of_v<IGreaperLibrary, T>, "Trying to get a GreaperLibrary "
				"but its implementation doesn't derive from IGreaperLibrary.");
			auto res = GetGreaperLibrary(libraryName);
			if(res.HasFailed())
				return CopyFailure<T*>(res);
			T* lib = reinterpret_cast<T*>(res.GetValue());
			return CreateResult(lib);
		}

		template<class T>
		Result<T*> GetGreaperLibraryT(const Uuid& libraryUUID)
		{
			static_assert(std::is_base_of_v<IGreaperLibrary, T>, "Trying to get a GreaperLibrary "
				"but its implementation doesn't derive from IGreaperLibrary.");
			auto res = GetGreaperLibrary(libraryUUID);
			if(res.HasFailed())
				return CopyFailure<T*>(res);
			T* lib = reinterpret_cast<T*>(res.GetValue());
			return CreateResult(lib);
		}

		template<class T, class ConfigType>
		EmptyResult RegisterInterfaceT(TInterface<T, ConfigType>* interface, ConfigType config = ConfigType{})
		{
			static_assert(std::is_base_of_v<IGreaperLibrary, T>, "Trying to register an Interface "
				"but its implementation doesn't derive from IInterface.");
			const auto res = RegisterInterface(interface);
			if(res.HasFailed())
				return res;
			interface->SetConfig(config);
			return res;
		}

		template<class T>
		Result<T*> GetInterfaceT(const Uuid& interfaceUUID)const
		{
			static_assert(IsInterface<T>::value, "Trying to get an interface that does not derive from IInterface.");
			auto res = GetInterface(interfaceUUID);
			if(res.HasFailed())
				return CopyFailure<T*>(res);
			T* interface = reinterpret_cast<T*>(res.GetValue());
			return CreateResult(interface);
		}

		template<class T>
		Result<T*> GetInterfaceT(const StringView& interfaceName)const
		{
			static_assert(IsInterface<T>::value, "Trying to get an interface that does not derive from IInterface.");
			auto res = GetInterface(interfaceName);
			if(res.HasFailed())
				return CopyFailure<T*>(res);
			T* interface = reinterpret_cast<T*>(res.GetValue());
			return CreateResult(interface);
		}

		template<class T>
		Result<T*> GetInterfaceT(const Uuid& interfaceUUID, const Uuid& libraryUUID)const
		{
			static_assert(IsInterface<T>::value, "Trying to get an interface that does not derive from IInterface.");
			auto res = GetInterface(interfaceUUID, libraryUUID);
			if(res.HasFailed())
				return CopyFailure<T*>(res);
			T* interface = reinterpret_cast<T*>(res.GetValue());
			return CreateResult(interface);
		}

		template<class T>
		Result<T*> GetInterfaceT(const StringView& interfaceName, const StringView& libraryName)const
		{
			static_assert(IsInterface<T>::value, "Trying to get an interface that does not derive from IInterface.");
			auto res = GetInterface(interfaceName, libraryName);
			if(res.HasFailed())
				return CopyFailure<T*>(res);
			T* interface = reinterpret_cast<T*>(res.GetValue());
			return CreateResult(interface);
		}

		template<class T>
		Result<T*> GetInterfaceT(const Uuid& interfaceUUID, const StringView& libraryName)const
		{
			static_assert(IsInterface<T>::value, "Trying to get an interface that does not derive from IInterface.");
			auto res = GetInterface(interfaceUUID, libraryName);
			if(res.HasFailed())
				return CopyFailure<T*>(res);
			T* interface = reinterpret_cast<T*>(res.GetValue());
			return CreateResult(interface);
		}

		template<class T>
		Result<T*> GetInterfaceT(const StringView& interfaceName, const Uuid& libraryUUID)const
		{
			static_assert(IsInterface<T>::value, "Trying to get an interface that does not derive from IInterface.");
			auto res = GetInterface(interfaceName, libraryUUID);
			if(res.HasFailed())
				return CopyFailure<T*>(res);
			T* interface = reinterpret_cast<T*>(res.GetValue());
			return CreateResult(interface);
		}
	};
}

#endif /* CORE_I_APPLICATION_H */
