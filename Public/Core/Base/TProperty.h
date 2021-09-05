/***********************************************************************************
*   Copyright 2021 Marcos Sánchez Torrent.                                         *
*   All Rights Reserved.                                                           *
***********************************************************************************/

#pragma once

#ifndef CORE_T_PROPERTY_H
#define CORE_T_PROPERTY_H 1

#include "..\Memory.h"
#include "PropertyValidator.h"
#include "..\Event.h"

namespace greaper
{
	/**
	 * @brief Stores configuration information, that information must be able to be 
	 * serialized into a string. Works like a ConsoleVariable (ID Software like).
	 * A breaf documentation can be attached to the Property on the PropertyInfo
	 * variable. PropertyName must be unique, unless a conflict will ocurr.
	 * Properties can be static, created from the sources and not serialized, can
	 * be constant, they cannot be modified once created. Properties use a
	 * PropertyValidator, which as the name states, validates if the Property has
	 * a valid value, there are several types of validators and you can provide yours,
	 * extending TPropertyValidator.
	 * You must extend TProperty and give your implementation, implementing the methods
	 * ToString and FromString, so TProperty will be able to serialize it to String.
	 * 
	 * @tparam T - Base type of the property, must be a serializable type or a pod type 
	 */
	template<class T>
	class TProperty
	{
	public:
		using OnModificationEvt_t = Event<TProperty*>;

	protected:
		T m_Value;
		String m_PropertyName;
		String m_PropertyInfo;
		String m_StringValue;	// When a property is changed, needs to update this value
		OnModificationEvt_t m_OnModificationEvent;
		TPropertyValidator<T>* m_PropertyValidator;

		bool m_Static;		// Created at the start of the program cannot be saved
		bool m_Constant;	// Cannot be modified

		TProperty(String propertyName, T initialValue, String propertyInfo = String{}, bool isConstant = false,
			bool isStatic = false, TPropertyValidator<T>* validator = nullptr) noexcept
			:m_Value(initialValue)
			, m_PropertyName(std::move(propertyName))
			, m_PropertInfo(std::move(propertyInfo))
			, m_PropertyValidator(validator)
			, m_Static(isStatic)
			, m_Constant(isConstant)
		{
			if (m_PropertyValidator == nullptr)
			{
				m_PropertyValidator = new PropertyValidatorNone<T>();
			}
			m_PropertyValidator->Validate(m_Value, &m_Value);
			m_StringValue = ToString(m_Value);
		}
		virtual String ToString(const T& value)const noexcept = 0;
		virtual T FromString(const String& value)const noexcept = 0;

	public:
		inline static constexpr int32 PropertyType = -1;
		using Value_t = T;

		[[nodiscard]] const String& GetPropertyName()const noexcept
		{
			return m_PropertyName;
		}
		[[nodiscard]] const String& GetPropertyInfo()const noexcept
		{
			return m_PropertyInfo;
		}
		[[nodiscard]] TPropertyValidator<T>* GetPropertyValidator()const noexcept
		{
			return m_PropertyValidator;
		}
		[[nodiscard]] bool IsConstant()const noexcept
		{
			return m_Constant;
		}
		[[nodiscard]] bool IsStatic()const noexcept
		{
			return m_Static;
		}
		bool SetValue(const T& value, bool triggerEvent = true) noexcept
		{
			if (m_Constant)
			{
				// TODO: log warning trying to change a constant property
				return false;
			}

			T old = m_Value;
			T newValue;
			if (!m_PropertyValidator->Validate(value, &newValue))
			{
				// TODO: log warning, cannot validate value
				return false;
			}
			m_Value = newValue;
			if (old == m_Value)
			{
				// TODO: log verbose, property has not changed
				return false; // Property has not changed;
			}
			m_StringValue = ToString(m_Value);
			if (triggerEvent)
				m_OnModificationEvent.Trigger(this);
			return true;
		}
		bool SetValueFromString(const String& value) noexcept
		{
			return SetValue(FromString(value));
		}
		[[nodiscard]] const T& GetValue()const noexcept
		{
			return m_Value;
		}
		[[nodiscard]] const String& GetStringValue()const noexcept
		{
			return m_StringValue;
		}
		[[nodiscard]] OnModificationEvt_t& GetOnModificationEvent() noexcept
		{
			return m_OnModificationEvent;
		}
	};
}

#endif /* CORE_T_PROPERTY_H */