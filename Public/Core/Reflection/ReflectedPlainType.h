/***********************************************************************************
*   Copyright 2021 Marcos Sánchez Torrent.                                         *
*   All Rights Reserved.                                                           *
***********************************************************************************/

#pragma once

#ifndef CORE_REFLECTION_REFLECTED_PLAIN_TYPE_H
#define CORE_REFLECTION_REFLECTED_PLAIN_TYPE_H 1

#include "../CorePrerequisites.h"
#include "../Stream.h"
#include "../Uuid.h"
#include <functional>

namespace greaper
{
	template<class T>
	struct ReflectedPlainType
	{
		static_assert(std::is_pod<T>::value,
			"Provided type isn't plain-old-data. You need to specialize ReflectedPlainType template in order to serialize this type. "\
			" (Or call ALLOW_MEMCPY_SERIALIZATION(type) macro if you are sure the type can be properly serialized using just memcpy.)");

		enum { ID = -1 }; enum { HasDynamicSize = 0 };

		static ReflectedSize_t ToStream(const T& data, IStream& stream);

		static ReflectedSize_t FromStream(T& data, IStream& stream);

		static ReflectedSize_t GetSize(const T& data);
	};

	template<typename T>
	ReflectedSize_t ReflectedSize(const T& data);

	template<typename T>
	ReflectedSize_t ReflectedWrite(const T& data, IStream& stream);

	template<typename T>
	ReflectedSize_t ReflectedRead(T& data, IStream& stream);

	template<class T>
	ReflectedSize_t ReflectedWriteWithSizeHeader(IStream& stream, const T& data, std::function<ReflectedSize_t()> fn);

	ReflectedSize_t ReflectedReadSizeHeader(IStream& stream, ReflectedSize_t& size);

	void ReflectedAddHeaderSize(ReflectedSize_t& size);
}

template<class T>
inline greaper::ReflectedSize_t greaper::ReflectedPlainType<T>::ToStream(const T& data, IStream& stream)
{
	return stream.WriteBytes((const uint8*)&data, GetSize(data));
}

template<class T>
inline greaper::ReflectedSize_t greaper::ReflectedPlainType<T>::FromStream(T& data, IStream& stream)
{
	return stream.ReadBytes((uint8*)&data, GetSize(data));
}

template<class T>
inline greaper::ReflectedSize_t greaper::ReflectedPlainType<T>::GetSize(const T& data)
{
	return sizeof(data);
}

template<typename T>
greaper::ReflectedSize_t greaper::ReflectedSize(const T& data)
{
	return ReflectedPlainType<T>::GetSize(data);
}

template<typename T>
greaper::ReflectedSize_t greaper::ReflectedWrite(const T& data, IStream& stream)
{
	return ReflectedPlainType<T>::ToStream(data, stream);
}

template<typename T>
greaper::ReflectedSize_t greaper::ReflectedRead(T& data, IStream& stream)
{
	return ReflectedPlainType<T>::FromStream(data, stream);
}

template<class T>
greaper::ReflectedSize_t greaper::ReflectedWriteWithSizeHeader(IStream& stream, const T& data, std::function<ReflectedSize_t()> fn)
{
	const auto sizePos = stream.Tell();
	ReflectedSize_t size = 0;
	stream.WriteBytes((const uint8*)&size, sizeof(size));
	size = fn() + sizeof(size);
	VerifyGreater(size, 0, "Trying to write a zero length type.");
	stream.Seek(sizePos);
	stream.WriteBytes(size);
	stream.Skip(size - sizeof(size));
	return size;
}

greaper::ReflectedSize_t greaper::ReflectedReadSizeHeader(IStream& stream, ReflectedSize_t& size)
{
	const auto byteSize = stream.ReadBytes((uint8*)&size, sizeof(size));
	return byteSize;
}

void greaper::ReflectedAddHeaderSize(ReflectedSize_t& size)
{
	size += sizeof(size);
}

#define ALLOW_MEMCPY_SERIALIZATION(type, id)											    \
namespace greaper{																    \
	static_assert(std::is_trivially_copyable_v<type>, #type " is not trivially copyable");	\
	template<>																				\
	struct ReflectedPlainType<type>															\
	{																						\
		enum { ID = id }; enum { HasDynamicSize = 0 };										\
																							\
		static ReflectedSize_t ToStream(const type& data, IStream& stream)					\
		{																					\
			return stream.WriteBytes((const uint8*)&data, sizeof(data));                    \
		}																					\
																							\
		static ReflectedSize_t FromStream(type& data, IStream& stream)						\
		{																					\
			return stream.ReadBytes((uint8*)&data, sizeof(data));                           \
		}																					\
																							\
		static ReflectedSize_t GetSize(const type& data)									\
		{																					\
			return sizeof(data);															\
		}																					\
	};																						\
}

ALLOW_MEMCPY_SERIALIZATION(bool,	greaper::RTI_Bool);
ALLOW_MEMCPY_SERIALIZATION(int8,	greaper::RTI_Int8);
ALLOW_MEMCPY_SERIALIZATION(uint8,	greaper::RTI_Uint8);
ALLOW_MEMCPY_SERIALIZATION(int16,	greaper::RTI_Int16);
ALLOW_MEMCPY_SERIALIZATION(uint16,	greaper::RTI_Uint16);
ALLOW_MEMCPY_SERIALIZATION(int32,	greaper::RTI_Int32);
ALLOW_MEMCPY_SERIALIZATION(uint32,	greaper::RTI_Uint32);
ALLOW_MEMCPY_SERIALIZATION(int64,	greaper::RTI_Int64);
ALLOW_MEMCPY_SERIALIZATION(uint64,	greaper::RTI_Uint64);
ALLOW_MEMCPY_SERIALIZATION(float,	greaper::RTI_Float);
ALLOW_MEMCPY_SERIALIZATION(double,	greaper::RTI_Double);
ALLOW_MEMCPY_SERIALIZATION(greaper::Uuid, greaper::RTI_UUID);
ALLOW_MEMCPY_SERIALIZATION(greaper::Half, greaper::RTI_Half);

#endif /* CORE_REFLECTION_REFLECTED_PLAIN_TYPE_H */