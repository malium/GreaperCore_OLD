/***********************************************************************************
*   Copyright 2021 Marcos Sánchez Torrent.                                         *
*   All Rights Reserved.                                                           *
***********************************************************************************/

#pragma once

#ifndef CORE_REFLECTION_I_REFLECTED_TYPE_H
#define CORE_REFLECTION_I_REFLECTED_TYPE_H 1

#include "../CorePrerequisites.h"
#include "../Memory.h"

namespace greaper
{
	class IReflectedTypeInfo;
	class IReflectedType
	{
	public:
		virtual ~IReflectedType() = default;

		virtual IReflectedTypeInfo* GetReflectedType()const = 0;

		bool IsDerivedFrom(IReflectedTypeInfo* base);

		ReflectedTypeID_t GetTypeID()const;

		const String& GetTypeName()const;
	};
}

#endif /* CORE_REFLECTION_I_REFLECTED_TYPE_H */