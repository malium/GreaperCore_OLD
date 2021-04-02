/***********************************************************************************
*   Copyright 2021 Marcos S�nchez Torrent.                                         *
*   All Rights Reserved.                                                           *
***********************************************************************************/

#pragma once

#ifndef GREAPER_CORE_UUID_H
#define GREAPER_CORE_UUID_H 1

#include "PHAL.h"
#include "Memory.h"

namespace greaper
{
	class Uuid
	{
		uint32 m_Data[4];

	public:
		INLINE constexpr Uuid()noexcept;
		INLINE constexpr Uuid(const uint32 data0, const uint32 data1, const uint32 data2, const uint32 data3)noexcept;
		INLINE constexpr explicit Uuid(const StringView& view)noexcept;
		INLINE constexpr Uuid(const Uuid& other)noexcept;
		INLINE constexpr Uuid(Uuid&& other)noexcept;
		INLINE constexpr Uuid& operator=(const Uuid& other)noexcept;
		INLINE constexpr Uuid& operator=(Uuid&& other)noexcept;
		~Uuid()noexcept = default;

		INLINE constexpr Uuid& operator=(const StringView& view);
		INLINE Uuid& operator=(const String& str);

		[[nodiscard]] INLINE String ToString()const;

		[[nodiscard]] INLINE static Uuid GenerateRandom();

		INLINE constexpr bool Empty()const noexcept;
		INLINE constexpr const uint32* GetData()const noexcept;

		friend bool operator==(const Uuid& left, const Uuid& right)noexcept;
		friend bool operator<(const Uuid& left, const Uuid& right)noexcept;
		friend struct std::hash<greaper::Uuid>;
	};
}

#include "Base/Uuid.inl"

#endif /* GREAPER_CORE_UUID_H */