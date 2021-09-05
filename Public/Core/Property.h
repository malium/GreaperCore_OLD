/***********************************************************************************
*   Copyright 2021 Marcos S�nchez Torrent.                                         *
*   All Rights Reserved.                                                           *
***********************************************************************************/

#pragma once

#ifndef CORE_PROPERTY_H
#define CORE_PROPERTY_H 1

#include "Memory.h"
#include "Base/TProperty.h"
#include "StringUtils.h"
#include "Event.h"
#include <string_view>

namespace greaper
{
	namespace EPropertyType
	{
		enum Type
		{
			Boolean = 0,
			Integer,
			Float,
			String,
			StringVector,
		};
	}
	class PropertyBool : public TProperty<bool>
	{
		String ToString(const Value_t& value)const noexcept override
		{
			return value ? "true" : "false";
		}
		Value_t FromString(const String& value)const noexcept override
		{
			return StringUtils::ToLower(value) == "true" ? true : false;
		}
	public:
		inline static constexpr int32 PropertyType = EPropertyType::Integer;
		PropertyBool(String propertyName, Value_t initialValue, String propertyInfo = String{}, bool isConstant = false,
			bool isStatic = false, TPropertyValidator<Value_t>* validator = nullptr)
			:TProperty(std::move(propertyName), initialValue, std::move(propertyInfo), isConstant, isStatic, validator)
		{

		}
	};

	class PropertyInt : public TProperty<int32>
	{
		String ToString(const Value_t& value)const noexcept override
		{
			using namespace std::string_view_literals;
			const auto conv = std::format("{}"sv, value);//std::to_string(value);
			return String{ conv.c_str(), conv.size() };
		}
		Value_t FromString(const String& value)const noexcept override
		{
			return std::strtol(value.c_str(), nullptr, 10);
		}
	public:
		inline static constexpr int32 PropertyType = EPropertyType::Integer;
		PropertyInt(String propertyName, Value_t initialValue, String propertyInfo = String{}, bool isConstant = false,
			bool isStatic = false, TPropertyValidator<Value_t>* validator = nullptr)
			:TProperty(std::move(propertyName), initialValue, std::move(propertyInfo), isConstant, isStatic, validator)
		{

		}
	};

	class PropertyFloat : public TProperty<float>
	{
		String ToString(const Value_t& value)const noexcept override
		{
			using namespace std::string_view_literals;
			const auto conv = std::format("{}"sv, value);//std::to_string(value);
			return String{ conv.c_str(), conv.size() };
		}
		Value_t FromString(const String& value)const noexcept override
		{
			return std::strtof(value.c_str(), nullptr);
		}
	public:
		inline static constexpr int32 PropertyType = EPropertyType::Float;
		PropertyFloat(String propertyName, Value_t initialValue, String propertyInfo = String{}, bool isConstant = false,
			bool isStatic = false, TPropertyValidator<Value_t>* validator = nullptr)
			:TProperty(std::move(propertyName), initialValue, std::move(propertyInfo), isConstant, isStatic, validator)
		{

		}
	};

	class PropertyString : public TProperty<String>
	{
		String ToString(const Value_t& value)const noexcept override
		{
			return value;
		}
		Value_t FromString(const String& value)const noexcept override
		{
			return value;
		}
	public:
		inline static constexpr int32 PropertyType = EPropertyType::String;
		PropertyString(String propertyName, Value_t initialValue, String propertyInfo = String{}, bool isConstant = false,
			bool isStatic = false, TPropertyValidator<Value_t>* validator = nullptr)
			:TProperty(std::move(propertyName), initialValue, std::move(propertyInfo), isConstant, isStatic, validator)
		{

		}
	};

	class PropertyStringVector : public TProperty<StringVec>
	{
		String ToString(const Value_t& value)const noexcept override
		{
			return StringUtils::ComposeString(value, ',');
		}
		Value_t FromString(const String& value)const noexcept override
		{
			return StringUtils::Tokenize(value, ',');
		}
	public:
		inline static constexpr int32 PropertyType = EPropertyType::StringVector;
		PropertyStringVector(String propertyName, Value_t initialValue, String propertyInfo = String{}, bool isConstant = false,
			bool isStatic = false, TPropertyValidator<Value_t>* validator = nullptr)
			:TProperty(std::move(propertyName), initialValue, std::move(propertyInfo), isConstant, isStatic, validator)
		{

		}
	};
}

#endif /* CORE_PROPERTY_H */