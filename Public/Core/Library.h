/***********************************************************************************
*   Copyright 2021 Marcos Sánchez Torrent.                                         *
*   All Rights Reserved.                                                           *
***********************************************************************************/

#pragma once

#ifndef CORE_I_LIBRARY_H
#define CORE_I_LIBRARY_H 1

#include "CorePrerequisites.h"

#if PLT_WINDOWS
#include "Win/WinLibrary.h"
#else
#error TODO: Library loading implementation in other platforms than windows
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

        INLINE void Open(const wchar* libraryName)
        {
            if(m_Handle != nullptr)
                return;
            m_Handle = OSLibrary::Load(libraryName);
        }

		INLINE void Close()
		{
			if(m_Handle == nullptr)
				return;
			OSLibrary::Unload(m_Handle);
			m_Handle = nullptr;
		}
		
		template<typename retType = void, class... types>
		INLINE typename FuncType<retType, types...>::Type GetFunc(const achar* funcName)noexcept
		{
			return reinterpret_cast<FuncType<retType, types...>::Type>(GetFunc(funcName));
		}

		Library(const Library&) = delete;
		Library& operator=(const Library&) = delete;
    };
}

#endif /* CORE_I_LIBRARY_H */
