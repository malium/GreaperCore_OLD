/***********************************************************************************
*   Copyright 2021 Marcos Sánchez Torrent.                                         *
*   All Rights Reserved.                                                           *
***********************************************************************************/

#pragma once

#ifndef CORE_GREAPER_LIBRARY_H
#define CORE_GREAPER_LIBRARY_H 1

#include "Library.h"
#include "Uuid.h"
#include "Property.h"

namespace greaper
{
	class IApplication;
	template<class T>
	class TProperty;
	class IProperty;
	template<class T>
	class TPropertyValidator;

	class IGreaperLibrary
	{
	protected:
		virtual void RegisterProperty(IProperty* property) = 0;

	public:
		static constexpr Uuid LibraryUUID = Uuid{ 0x10001000, 0x10001000, 0x10001000, 0x10001000 };
		static constexpr StringView LibraryName = StringView{ "Greaper Library" };

		virtual void InitLibrary(IApplication* app) = 0;

		virtual void DeinitLibrary() = 0;

		virtual const Uuid& GetLibraryUuid()const = 0;

		virtual const StringView& GetLibraryName()const = 0;

		virtual IApplication* GetApplication()const = 0;

		virtual Library* GetLibrary()const = 0;

		virtual Vector<IProperty*> GetPropeties()const = 0;

		virtual IProperty* GetProperty(const String& name)const = 0;

		template<class T, class _Alloc_>
		friend TProperty<T>* CreateProperty(greaper::IGreaperLibrary*, String, T, String, bool, bool, TPropertyValidator<T>*);
	};

	template<class T, class _Alloc_ = greaper::GenericAllocator>
	TProperty<T>* CreateProperty(IGreaperLibrary* library, String propertyName, T initialValue, String propertyInfo = String{},
		bool isConstant = false, bool isStatic = false, TPropertyValidator<T>* validator = nullptr)
	{
		TProperty<T>* property = AllocAT(TProperty<T>, _Alloc_);
		new ((void*)property)TProperty(std::move(propertyName), std::move(initialValue), std::move(propertyInfo), isConstant, isStatic, validator);
		library->RegisterProperty((IProperty*)property);
		return property;
	}

	template<class T>
	TProperty<T>* GetProperty(IGreaperLibrary* library, const String& name)
	{
		IProperty* prop = library->GetProperty(name);
		if (!prop)
			return nullptr;
		return reinterpret_cast<TProperty<T>>(prop);
	}
}

#endif /* CORE_GREAPER_LIBRARY_H */