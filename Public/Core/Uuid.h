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
	/**
	 * @brief Is a cross-platform universally unique identifier struct
	 * 
	 * Instead of the typical 8-4-4-4-12 representation it uses 8-8-8-8 representation,
	 * it is used across all interfaces, libraries and resources.
	 */
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
		INLINE void FromString(const String& str) noexcept;

		/**
		 * @brief Requests to the OS a random Uuid
		 * 
		 * @return Uuid The new random Uuid 
		 */
		[[nodiscard]] INLINE static Uuid GenerateRandom() noexcept;

		INLINE constexpr bool IsEmpty()const noexcept;
		INLINE constexpr const uint32* GetData()const noexcept;
		
		INLINE static constexpr Uuid Empty()noexcept;

		friend constexpr bool operator==(const Uuid& left, const Uuid& right)noexcept;
		friend constexpr bool operator<(const Uuid& left, const Uuid& right)noexcept;
		
		friend struct std::hash<greaper::Uuid>;
	};

	template<> struct ReflectedTypeToID<Uuid> { static constexpr ReflectedTypeID_t ID = RTI_UUID; };
}

#include "Base/Uuid.inl"

#endif /* GREAPER_CORE_UUID_H */