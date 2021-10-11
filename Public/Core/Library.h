/***********************************************************************************
*   Copyright 2021 Marcos Sánchez Torrent.                                         *
*   All Rights Reserved.                                                           *
***********************************************************************************/

#pragma once

#ifndef CORE_LIBRARY_H
#define CORE_LIBRARY_H 1

#include "CorePrerequisites.h"

#if PLT_WINDOWS
#include "Win/WinLibrary.h"
#else
#include "Lnx/LnxLibrary.h"
#endif

namespace greaper
{
	template<class retType, class... types>
	struct FuncType
	{
		using Type = retType(*)(types...);
	};
    class Library
    {
        OSLibrary::LibraryHandle m_Handle;

    public:
        INLINE constexpr Library()noexcept
            :m_Handle(nullptr)
        {
            
        }

        INLINE Library(const wchar* libraryName)noexcept
            :m_Handle(nullptr)
        {
            Open(libraryName);
        }

		INLINE Library(const achar* libraryName)noexcept
			:m_Handle(nullptr)
		{
			Open(libraryName);
		}

		constexpr INLINE Library(Library&& other)noexcept
			:m_Handle(other.m_Handle)
		{
			other.m_Handle = nullptr;
		}

		constexpr INLINE Library& operator=(Library&& other)noexcept
		{
			if(this != &other)
			{
				Close();
				m_Handle = other.m_Handle;
				other.m_Handle = nullptr;
			}
			return *this;
		}

		INLINE void Open(const achar* libraryName)
		{
			if (IsOpen())
				return;
			m_Handle = OSLibrary::Load(libraryName);
		}

        INLINE void Open(const wchar* libraryName)
        {
			if (IsOpen())
				return;
            m_Handle = OSLibrary::Load(libraryName);
        }

		INLINE void Close()
		{
			if (!IsOpen())
				return;
			OSLibrary::Unload(m_Handle);
			m_Handle = nullptr;
		}

		INLINE constexpr bool IsOpen()const noexcept
		{
			return m_Handle != nullptr;
		}

		INLINE FuncPtr GetFunction(const achar* funcName)const noexcept
		{
			if (!IsOpen())
				return nullptr;
			return OSLibrary::FuncLoad(m_Handle, funcName);
		}
		
		template<typename retType = void, class... types>
		INLINE typename FuncType<retType, types...>::Type GetFunctionT(const achar* funcName)const noexcept
		{
			//if (!IsOpen())
			//	return nullptr;

			return reinterpret_cast<FuncType<retType, types...>::Type>(GetFunction(funcName));
		}

		Library(const Library&) = delete;
		Library& operator=(const Library&) = delete;
    };
}

#endif /* CORE_LIBRARY_H */
