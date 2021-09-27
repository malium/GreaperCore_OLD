/***********************************************************************************
*   Copyright 2021 Marcos Sánchez Torrent.                                         *
*   All Rights Reserved.                                                           *
***********************************************************************************/

#pragma once

#ifndef CORE_I_THREAD_MANAGER_H
#define CORE_I_THREAD_MANAGER_H 1

#include "CorePrerequisites.h"
#include "Interface.h"
#include "Base/IThread.h"
#include <optional>

namespace greaper
{
	class IThreadManager
	{
	public:
		static constexpr Uuid InterfaceUUID = Uuid{ 0x284B5BAD, 0x9B004E76, 0x8B7F76DD, 0xB45D740F };
		static constexpr StringView InterfaceName = "ThreadManager"sv;

		virtual ~IThreadManager()noexcept = default;

		virtual const Uuid& GetInterfaceUUID()const = 0;

		virtual const StringView& GetInterfaceName()const = 0;

		virtual IGreaperLibrary* GetLibrary()const = 0;

		virtual std::optional<IThread*> GetThread(ThreadID_t id)const = 0;

		virtual std::optional<IThread*> GetThread(const String& threadName)const = 0;

		virtual std::optional<IThread*> CreateThread(const ThreadConfig& config) = 0;

		virtual void DestroyThread(IThread* thread) = 0;
	};
}

#endif /* CORE_I_THREAD_MANAGER_H */