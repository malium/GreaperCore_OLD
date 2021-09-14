/***********************************************************************************
*   Copyright 2021 Marcos Sánchez Torrent.                                         *
*   All Rights Reserved.                                                           *
***********************************************************************************/

#pragma once

#ifndef CORE_I_LOG_MANAGER_H
#define CORE_I_LOG_MANAGER_H 1

#include "Interface.h"

namespace greaper
{
	namespace ELogLevel
	{
		enum Type
		{
			VERBOSE,
			INFORMATIVE,
			WARNING,
			ERROR,
			CRITICAL
		};
	}
	using LogLevel_t = ELogLevel::Type;

	struct LogData
	{
		String Message;
		Timepoint_t Time;
		LogLevel_t Level;
	};

	class ILogManager : public IInterface
	{
	public:
		static constexpr Uuid InterfaceUUID = Uuid{ 0xB05DBD1D, 0x83FE42E1, 0x90CFF1EE, 0x2434CD0D };
		static constexpr StringView InterfaceName = StringView{ "LogManager" };

		using OnLoggedMessageEvent_t = Event<LogData>;

		virtual ~ILogManager()noexcept = default;

		virtual const Uuid& GetInterfaceUUID()const = 0;

		virtual const StringView& GetInterfaceName()const = 0;

		virtual IGreaperLibrary* GetLibrary()const = 0;

		virtual OnLoggedMessageEvent_t* GetOnLoggedEvent() = 0;

		virtual void Log(LogLevel_t level, const String& message) = 0;
	};
}

#endif /* CORE_I_LOG_MANAGER_H */
