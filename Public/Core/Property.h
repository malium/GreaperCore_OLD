/***********************************************************************************
*   Copyright 2021 Marcos Sánchez Torrent.                                         *
*   All Rights Reserved.                                                           *
***********************************************************************************/

#pragma once

#ifndef CORE_PROPERTY_H
#define CORE_PROPERTY_H 1

#include "Memory.h"
#include "Base/PropertyValidator.h"
#include "Base/PropertyConverter.h"
#include "Event.h"

namespace greaper
{
	class IProperty
	{
	public:
		using OnModificationEvent_t = Event<IProperty*>;
		
		virtual [[nodiscard]] const String& GetPropertyName()const noexcept = 0;
		virtual [[nodiscard]] const String& GetPropertyInfo()const noexcept = 0;
		virtual [[nodiscard]] bool IsConstant()const noexcept = 0;
		virtual [[nodiscard]] bool IsStatic()const noexcept = 0;
		virtual [[nodiscard]] bool SetValueFromString(const String& value)noexcept = 0;
		virtual [[nodiscard]] const String& GetStringValue()const noexcept = 0;
		virtual [[nodiscard]] OnModificationEvent_t* GetModificationEvent()noexcept = 0;
	};
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
	class TProperty : public IProperty
	{
		T m_Value;
		String m_PropertyName;
		String m_PropertyInfo;
		String m_StringValue;	// When a property is changed, needs to update this value
		OnModificationEvent_t m_OnModificationEvent;
		TPropertyValidator<T>* m_PropertyValidator;

		bool m_Static;		// Created at the start of the program cannot be saved
		bool m_Constant;	// Cannot be modified

		TProperty(String propertyName, T initialValue, String propertyInfo = String{}, bool isConstant = false,
			bool isStatic = false, TPropertyValidator<T>* validator = nullptr) noexcept
			:m_Value(initialValue)
			, m_PropertyName(std::move(propertyName))
			, m_PropertyInfo(std::move(propertyInfo))
			, m_PropertyValidator(validator)
			, m_Static(isStatic)
			, m_Constant(isConstant)
		{
			if (m_PropertyValidator == nullptr)
			{
				m_PropertyValidator = new PropertyValidatorNone<T>();
			}
			m_PropertyValidator->Validate(m_Value, &m_Value);
			m_StringValue = TPropertyConverter<T>::ToString(m_Value);
		}

		template<class T, class _Alloc_>
		friend TProperty<T>* CreateProperty(greaper::IGreaperLibrary*, String, T, String, bool, bool, TPropertyValidator<T>*);
	public:
		using value_type = T;

		/*static TProperty<T>* Create(String propertyName, T initialValue, String propertyInfo = String{}, bool isConstant = false,
			TPropertyValidator<T>* validator = nullptr)
		{
			TProperty<T>* p = AllocT(TProperty<T>);
			new((void*)p)TProperty<T>(std::move(propertyName), initialValue, std::move(propertyInfo), isConstant, false, validator);
			return p;
		}
		static TProperty<T>* CreateStatic(StringView propertyName, T initialValue, StringView propertyInfo = StringView{}, bool isConstant = false,
			TPropertyValidator<T>* validator = nullptr)
		{
			TProperty<T>* p = AllocT(TProperty<T>);
			new((void*)p)TProperty<T>(String{ propertyName }, initialValue, String{ propertyInfo }, isConstant, true, validator);
			return p;
		}*/

		[[nodiscard]] const String& GetPropertyName()const noexcept override
		{
			return m_PropertyName;
		}
		[[nodiscard]] const String& GetPropertyInfo()const noexcept override
		{
			return m_PropertyInfo;
		}
		[[nodiscard]] TPropertyValidator<T>* GetPropertyValidator()const noexcept
		{
			return m_PropertyValidator;
		}
		[[nodiscard]] bool IsConstant()const noexcept override
		{
			return m_Constant;
		}
		[[nodiscard]] bool IsStatic()const noexcept override
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
			m_StringValue = TPropertyConverter<T>::ToString(m_Value);
			if (triggerEvent)
				m_OnModificationEvent.Trigger(this);
			return true;
		}
		bool SetValueFromString(const String& value) noexcept override
		{
			return SetValue(TPropertyConverter<T>::FromString(value));
		}
		[[nodiscard]] const T& GetValue()const noexcept
		{
			return m_Value;
		}
		[[nodiscard]] const String& GetStringValue()const noexcept override
		{
			return m_StringValue;
		}
		[[nodiscard]] OnModificationEvent_t* GetModificationEvent() noexcept override
		{
			return &m_OnModificationEvent;
		}
	};
	using PropertyBool = TProperty<bool>;
	using PropertyInt = TProperty<int32>;
	using PropertyFloat = TProperty<float>;
	using PropertyString = TProperty<String>;
	using PropertyStringVec = TProperty<StringVec>;

	template<typename T> struct ReflectedTypeToID<TProperty<T>> { static constexpr ReflectedTypeID_t ID = RTI_Property; };
}

#endif /* CORE_PROPERTY_H */