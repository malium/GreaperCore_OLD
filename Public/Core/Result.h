/***********************************************************************************
*   Copyright 2021 Marcos S�nchez Torrent.                                         *
*   All Rights Reserved.                                                           *
***********************************************************************************/

#pragma once

#ifndef CORE_RESULT_H
#define CORE_RESULT_H 1

#include "CorePrerequisites.h"
#include "Memory.h"

namespace greaper
{
	struct EmptyStruct {  };
	template<class T>
	class Result
	{
		String m_FailMessage;
		T m_Value;
		bool m_Failure = false;

		template<class T> friend Result<T> CreateResult(T) noexcept;
		template<class T> friend Result<T> CreateFailure(String) noexcept;
		template<class T> friend Result<T> CreateFailure(StringView) noexcept;
		friend Result<EmptyStruct> CreateEmptyResult() noexcept;

		Result() = default;

	public:
		bool IsOk()const noexcept { return !m_Failure; }

		bool HasFailed()const noexcept { return m_Failure; }

		const String& GetFailMessage()const noexcept { return m_FailMessage; }

		T& GetValue() noexcept;

		const T& GetValue()const noexcept;
	};

	using EmptyResult = Result<EmptyStruct>;

	template<class T>
	Result<T> CreateResult(T value) noexcept
	{
		Result<T> res;
		res.m_Value = std::move(value);
		res.m_Failure = false;
		return res;
	}

	Result<EmptyStruct> CreateEmptyResult() noexcept
	{
		Result<EmptyStruct> res;
		res.m_Failure = false;
		return res;
	}

	template<class T>
	Result<T> CreateFailure(String errorMessage) noexcept
	{
		Result<T> res;
		res.m_FailMessage = std::move(errorMessage);
		res.m_Failure = true;
		return std::move(res);
	}

	template<class T>
	Result<T> CreateFailure(StringView errorMessage) noexcept
	{
		Result<T> res;
		res.m_FailMessage.assign(errorMessage);
		res.m_Failure = true;
		return std::move(res);
	}

	template<class T, class U = T>
	Result<T> CopyFailure(Result<U> res) noexcept
	{
		Result<T> r;
		r.m_Failure = true;
		r.m_FailMessage = std::move(res.m_FailMessage);
		return std::move(r);
	}

	template<class T>
	INLINE T& greaper::Result<T>::GetValue() noexcept
	{
		Verify(IsOk(), "Trying to optain a failed result, msg: '%s'.", m_FailMessage.c_str());
		return m_Value;
	}
	
	template<class T>
	INLINE const T& greaper::Result<T>::GetValue() const noexcept
	{
		Verify(IsOk(), "Trying to optain a failed result, msg: '%s'.", m_FailMessage.c_str());
		return m_Value;
	}
}

#endif /* CORE_RESULT_H */