/***********************************************************************************
*   Copyright 2021 Marcos Sánchez Torrent.                                         *
*   All Rights Reserved.                                                           *
***********************************************************************************/

#pragma once

#ifndef CORE_PROPERTY_CONVERTER_H
#define CORE_PROPERTY_CONVERTER_H 1

#include "../Memory.h"
#include "../StringUtils.h"
#ifdef __cpp_lib_format
#include <format>
#endif

namespace greaper
{
	template<class T>
	struct TPropertyConverter
	{
		static_assert(false, "Trying to use a property type not overloaded by a valid TPropertyConverter")
		static String ToString(const T& value)
		{
			return {};
		}
		static T FromString(const String& value)
		{
			return T();
		}
	};

	template<>
	struct TPropertyConverter<bool>
	{
		static String ToString(const bool& value)
		{
			return value ? "true" : "false";
		}
		static bool FromString(const String& value)
		{
			return StringUtils::ToLower(value) == "true" ? true : false;
		}
	};

	template<>
	struct TPropertyConverter<int32>
	{
		static String ToString(const int32& value)
		{
			const auto conv =
#ifdef _FORMAT_
				std::format("{}"sv, value);
#else
				std::to_string(value);
#endif
			return String{ conv.c_str(), conv.size() };
		}
		static int32 FromString(const String& value)
		{
			return std::strtol(value.c_str(), nullptr, 10);
		}
	};

	template<>
	struct TPropertyConverter<float>
	{
		static String ToString(const float& value)
		{
			const auto conv =
#ifdef _FORMAT_
				std::format("{}"sv, value);
#else
				std::to_string(value);
#endif
			return String{ conv.c_str(), conv.size() };
		}
		static float FromString(const String& value)
		{
			return std::strtof(value.c_str(), nullptr);
		}
	};

	template<>
	struct TPropertyConverter<String>
	{
		static String ToString(const String& value)
		{
			return value;
		}
		static String FromString(const String& value)
		{
			return value;
		}
	};

	template<>
	struct TPropertyConverter<StringVec>
	{
		static String ToString(const StringVec& value)
		{
			return StringUtils::ComposeString(value, ',');
		}
		static StringVec FromString(const String& value)
		{
			return StringUtils::Tokenize(value, ',');
		}
	};
}

#endif /* CORE_PROPERTY_CONVERTER_H */