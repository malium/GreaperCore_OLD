/***********************************************************************************
*   Copyright 2021 Marcos Sánchez Torrent.                                         *
*   All Rights Reserved.                                                           *
***********************************************************************************/

#pragma once

#ifndef CORE_REFLECTION_REFLECTED_PROPERTY_H
#define CORE_REFLECTION_REFLECTED_PROPERTY_H 1

#include "../CorePrerequisites.h"
#include "ReflectedPlainType.h"
#include "../Property.h"

namespace greaper
{
	template<class T>
	struct ReflectedPlainType<TProperty<T>>
	{
		enum { ID = RTI_Property }; enum { HasDynamicSize = 1 };

		static ReflectedSize_t ToStream(const TProperty<T>& data, IStream& stream)
		{
			return ReflectedWriteWithSizeHeader(stream, data, [&data, &stream]()
				{
					const auto& name = data.GetPropertyName();
					const auto& value = data.GetStringValue();
					const sizet nameLength = name.size();
					const sizet valueLength = value.size();
					ReflectedSize_t size = (nameLength + valueLength) * sizeof(String::value_type) + sizeof(nameLength) + sizeof(valueLength);
					stream.WriteBytes((const uint8*)&nameLength, sizeof(nameLength));
					stream.WriteBytes((const uint8*)&valueLength, sizeof(valueLength));
					stream.WriteBytes((const uint8*)name.data(), nameLength * sizeof(String::value_type));
					stream.WriteBytes((const uint8*)value.data(), valueLength * sizeof(String::value_type));
					return size;
				});
		}

		static ReflectedSize_t FromStream(TProperty<T>& data, IStream& stream)
		{
			ReflectedSize_t size = 0;

			ReflectedReadSizeHeader(stream, size);

			const auto propertySize = size - sizeof(ReflectedSize_t);
			sizet nameLength = 0, valueLength = 0;
			stream.ReadBytes((uint8*)&nameLength, sizeof(nameLength));
			stream.ReadBytes((uint8*)&valueLength, sizeof(valueLength));
			
			auto name = String(nameLength, (achar)0);
			auto value = String(valueLength, (achar)0);

			stream.ReadBytes((uint8*)name.data(), nameLength * sizeof(String::value_type));
			stream.ReadBytes((uint8*)value.data(), valueLength * sizeof(String::value_type));

			VerifyEqual(name, data.GetPropertyName(), "Trying to deserialize a Property with different name.");

			data.SetValueFromString(value);

			return size;
		}

		static ReflectedSize_t GetSize(const TProperty<T>& data)
		{
			const auto& name = data.GetPropertyName();
			const auto& value = data.GetStringValue();
			const sizet nameLength = name.size();
			const sizet valueLength = value.size();
			ReflectedSize_t dataSize = (nameLength + valueLength) * sizeof(String::value_type) + sizeof(nameLength) + sizeof(valueLength);
			ReflectedAddHeaderSize(dataSize); // Size Header

			return dataSize;
		}
	};
}

#endif /* CORE_REFLECTION_REFLECTED_PROPERTY_H */