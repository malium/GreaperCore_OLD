/***********************************************************************************
*   Copyright 2021 Marcos S�nchez Torrent.                                         *
*   All Rights Reserved.                                                           *
***********************************************************************************/

#pragma once

#ifndef CORE_I_TIME_MANAGER_H
#define CORE_I_TIME_MANAGER_H 1

#include "Interface.h"

namespace greaper
{
	class ITimeManager : public IInterface
	{
	public:
		static constexpr Uuid InterfaceUUID = Uuid{ 0x7646A5C7, 0x81254E1C, 0x80D21DEE, 0x3ADAAAA4 };
		static constexpr StringView InterfaceName = "TimeManager"sv;

		virtual ~ITimeManager()noexcept = default;

		virtual const Uuid& GetInterfaceUUID()const = 0;

		virtual const StringView& GetInterfaceName()const = 0;

		virtual IGreaperLibrary* GetLibrary()const = 0;

		virtual void PreUpdate() = 0;

		virtual void Update() = 0;

		virtual void PostUpdate() = 0;

		virtual void FixedUpdate() = 0;

		virtual Timepoint_t GetTimeSinceStart()const = 0;

		virtual Timepoint_t GetTimeSinceLastUpdate()const = 0;

		virtual Timepoint_t GetTimeSinceLastFixedUpdate()const = 0;

		virtual uint64 GetCurrentFrame()const = 0;

		virtual Duration_t GetUpdateDeltaTime()const = 0;

		virtual Duration_t GetFixedUpdateDeltaTime()const = 0;

		virtual void SetMaxUpdateRate(int32 updatesPerSecond) = 0;

		virtual int32 GetMaxUpdateRate()const = 0;
	};
}

#endif /* CORE_I_TIME_MANAGER_H */