/***********************************************************************************
*   Copyright 2021 Marcos Sánchez Torrent.                                         *
*   All Rights Reserved.                                                           *
***********************************************************************************/

#pragma once

#ifndef CORE_REFLECTION_REFLECTED_TYPE_INFO_H
#define CORE_REFLECTION_REFLECTED_TYPE_INFO_H 1

#include "../CorePrerequisites.h"
#include "../Enumeration.h"

namespace greaper
{
	struct IReflectedField;
	class IReflectedType;

	class IReflectedTypeInfo
	{
		Vector<IReflectedField*> m_Fields;

	protected:
		void AddNewField(IReflectedField* field);

	public:
		IReflectedTypeInfo() = default;

		virtual ~IReflectedTypeInfo();

		virtual Vector<IReflectedTypeInfo*>& GetDerivedClasses() = 0;

		virtual IReflectedTypeInfo* GetBaseType() = 0;

		virtual bool IsDerivedFrom(IReflectedTypeInfo* base) = 0;

		virtual SPtr<IReflectedType> NewRelfectedObject() = 0;

		virtual const String& GetReflectedName() = 0;

		virtual ReflectedTypeID_t GetReflectedTypeID() = 0;

		virtual void OnSerializationStarted(IReflectedType* obj)
		{
			UNUSED(obj);
		}

		virtual void OnSerializationEnded(IReflectedType* obj)
		{
			UNUSED(obj);
		}

		virtual void OnDeserializationStarted(IReflectedType* obj)
		{
			UNUSED(obj);
		}

		virtual void OnDeserializationEnded(IReflectedType* obj)
		{
			UNUSED(obj);
		}

		uint32 GetFieldCount()const;

		IReflectedField* GetField(sizet index);

		IReflectedField* FindField(const String& name);

		IReflectedField* FindField(ReflectedFieldID_t fieldID);

		virtual void _RegisterDerivedClass(IReflectedTypeInfo* derivedClass) = 0;

		virtual IReflectedTypeInfo* _Clone() = 0;
	};
}

#endif /* CORE_REFLECTION_REFLECTED_TYPE_INFO_H */