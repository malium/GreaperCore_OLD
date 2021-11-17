/***********************************************************************************
*   Copyright 2021 Marcos Sánchez Torrent.                                         *
*   All Rights Reserved.                                                           *
***********************************************************************************/

#pragma once

#ifndef CORE_GREAPER_LIBRARY_H
#define CORE_GREAPER_LIBRARY_H 1

#include "Library.h"
#include "Uuid.h"
#include "Result.h"

namespace greaper
{
	class IGreaperLibrary
	{
	protected:
		virtual bool RegisterProperty(IProperty* property) = 0;

	public:
		static constexpr Uuid LibraryUUID = Uuid{  };
		static constexpr StringView LibraryName = StringView{ "Unknown Greaper Library" };

		virtual ~IGreaperLibrary() = default;

		virtual void InitLibrary(IApplication* app) = 0;

		virtual void InitManagers() = 0;

		virtual void InitProperties() = 0;

		virtual void InitReflection() = 0;

		virtual void DeinitLibrary() = 0;

		virtual const Uuid& GetLibraryUuid()const = 0;

		virtual const StringView& GetLibraryName()const = 0;

		virtual IApplication* GetApplication()const = 0;

		virtual const Library* GetOSLibrary()const = 0;

		virtual Vector<IProperty*> GetPropeties()const = 0;

		virtual Result<IProperty*> GetProperty(const String& name)const = 0;

		virtual void LogVerbose(const String& message) = 0;

		virtual void Log(const String& message) = 0;

		virtual void LogWarning(const String& message) = 0;

		virtual void LogError(const String& message) = 0;

		virtual void LogCritical(const String& message) = 0;

		template<class T, class _Alloc_>
		friend Result<TProperty<T>*> CreateProperty(greaper::IGreaperLibrary*, const StringView&, T, const StringView&,
			bool, bool, TPropertyValidator<T>*);
	};

	template<class T>
	struct ValidGreaperLibrary
	{
		static_assert(std::is_base_of_v<IGreaperLibrary, T>, "Trying to validate a GreaperLibrary that does not derive from IGreaperLibrary");
		static constexpr bool UUIDValid = T::LibraryUUID != IGreaperLibrary::LibraryUUID;
		static constexpr bool NameValid = T::LibraryName != IGreaperLibrary::LibraryName;

		static constexpr bool Valid = UUIDValid && NameValid;
	};
}

#endif /* CORE_GREAPER_LIBRARY_H */