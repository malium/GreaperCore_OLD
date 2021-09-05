/***********************************************************************************
*   Copyright 2021 Marcos Sánchez Torrent.                                         *
*   All Rights Reserved.                                                           *
***********************************************************************************/

#pragma once

#ifndef GREAPER_CORE_UUID_H
#define GREAPER_CORE_UUID_H 1

#include "CorePrerequisites.h"
#include "Memory.h"

namespace greaper
{
	class Uuid
	{
		uint32 m_Data[4]{ 0, 0, 0, 0 };

	public:
		INLINE constexpr Uuid() noexcept = default;
		INLINE constexpr Uuid(const uint32 data0, const uint32 data1, const uint32 data2, const uint32 data3) noexcept;
		INLINE constexpr explicit Uuid(const StringView& view) noexcept;
		INLINE constexpr Uuid(const Uuid& other) noexcept = default;
		INLINE constexpr Uuid(Uuid&& other) noexcept = default;
		INLINE Uuid& operator=(const Uuid& other) noexcept = default;
		INLINE Uuid& operator=(Uuid&& other) noexcept = default;
		~Uuid()noexcept = default;

		INLINE Uuid& operator=(const StringView& view) noexcept;
		INLINE Uuid& operator=(const String& str) noexcept;

		[[nodiscard]] INLINE String ToString()const noexcept;

		[[nodiscard]] INLINE static Uuid GenerateRandom() noexcept;

		INLINE constexpr bool Empty()const noexcept;
		INLINE constexpr const uint32* GetData()const noexcept;

		friend bool operator==(const Uuid& left, const Uuid& right)noexcept;
		friend bool operator<(const Uuid& left, const Uuid& right)noexcept;
		friend struct std::hash<greaper::Uuid>;
	};
}

#include "Base/Uuid.inl"

#endif /* GREAPER_CORE_UUID_H */