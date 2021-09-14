/***********************************************************************************
*   Copyright 2021 Marcos Sánchez Torrent.                                         *
*   All Rights Reserved.                                                           *
***********************************************************************************/

#pragma once

/** Checks if a value is within range (min,max], inclusive on max and min */
template<typename T>
INLINE constexpr bool IsWithin(const T& value, const T& min, const T& max)
{
	return value > min && value <= max;
}
/** Checks if a value is within range [min, max], inclusive on max and min */
template<class T>
INLINE constexpr bool IsWithinInclusive(const T& value, const T& min, const T& max)
{
	return value >= min && value <= max;
}
INLINE constexpr uint32 BitsLog2(uint32 v)
{
	if (v == 16) return 4; if (v == 32) return 5; if (v == 64) return 6; return 3;
}
/** Checks if a number is a power of two */
template<typename T>
INLINE constexpr bool IsPowerOfTwo(const T value)
{
	return !(value == 0) && !(value & (value - 1));
}
/** Rounds number up/down to the next multiple, multiple must be power of two */
template<typename T>
INLINE constexpr T RoundUp(const T number, const T multiple)
{
	static_assert(!IsPowerOfTwo(multiple), "Multiple must be power of two.");
	const T result = (number + multiple - 1) & ~(multiple - 1);
	static_assert(number <= result && result < number + multiple, "");
	return result;
}
/** Rounds the given number up to the next higher power of two */
template<typename T>
INLINE constexpr T RoundUpToPowerOf2(T val)
{
	--val;
	val |= val >> 1;
	val |= val >> 2;
	val |= val >> 4;
	val |= val >> 8;
	val |= val >> 16;
	++val;
	return val;
}
/** Returns the highest of 3 values */
template<typename T>
INLINE constexpr T Max3(const T a, const T b, const T c)
{
	return (a > b) ? ((a > c) ? a : c) : ((b > c) ? b : c);
}
/** Returns the lowest of 3 values */
template<typename T>
INLINE constexpr T Min3(const T a, const T b, const T c)
{
	return (a < b) ? ((a < c) ? a : c) : ((b < c) ? b : c);
}
/** Returns a higher value */
template<class T>
INLINE constexpr T Max(const T a, const T b)
{
	return (a >= b) ? a : b;
}
/** Returns the lower value */
template<class T>
INLINE constexpr T Min(const T a, const T b)
{
	return (a <= b) ? a : b;
}
/** Clamps the value between a minimum and a maximum */
template<typename T>
INLINE constexpr T Clamp(const T a, const T min, const T max)
{
	return Max(min, Min(max, a));
}
/** Computes the absolute value */
template<class T>
INLINE constexpr T Abs(const T a)
{
	return (a >= (T)0) ? a : -a;
}
/** Returns a * a */
template<typename T>
INLINE constexpr T Square(const T a)
{
	return a * a;
}
/** Returns a * a * a */
template<typename T>
INLINE constexpr T Cube(const T a)
{
	return a * a * a;
}
/** Returns 1, 0 or -1 depending on relation of T to 0 */
template<class T>
INLINE constexpr T Sign(const T a)
{
	return ((a > (T)0) ? (T)1 : ((a) < (T)0) ? (T)-1 : (T)0);
}

/** Clamps an int32 into the int8 range. */
INLINE constexpr int8 ClampChar(const int32 i)
{
	return static_cast<int8>(Clamp(i, -128, 127));
}
/** Clamps an int32 into the int16 range. */
INLINE constexpr int16 ClampShort(const int32 i)
{
	return static_cast<int16>(Clamp(i, -32768, 32767));
}
/** Retruns true if value is NaN */
INLINE constexpr bool IsNaN(const float f)noexcept
{
	return (*reinterpret_cast<const uint32*>(&f) & 0x7FFFFFFF) > 0x7F800000;
}
/** Returns true if a value is finite */
INLINE constexpr bool IsFinite(const float f)
{
	return (*reinterpret_cast<const uint32*>(&f) & 0x7F800000) != 0x7F800000;
}
/** Returns true if a value is infinite */
INLINE constexpr bool IsInfinite(const float f)
{
	return !IsFinite(f);
}
/** Get the boolean value from a flag */
INLINE bool GetBitValue(const uint8* ptr, const uint32 index)noexcept
{
	const auto* const bytePtr = ptr + index / 8;
	const uint8 mask = 1 << (index & 0x7);
	return (*bytePtr & mask) != 0;
}
/** Set the boolean value to a flag */
INLINE bool SetBitValue(uint8* ptr, const uint32 index, const bool set)noexcept
{
	const auto bytePtr = ptr + index / 8;
	const uint8 mask = 1 << (index & 0x7);
	if (set)
		*bytePtr |= mask;
	else
		*bytePtr &= ~mask;
}

/***********************************************************************************
*                              HASH HELPER FUNCITONS                               *
***********************************************************************************/
namespace std { template<class T>struct hash; }
/**
*	Computes the hash of a type given the seed.
*/
template<typename T>
INLINE void HashCombine(sizet& seed, const T& val)
{
	seed ^= std::hash<T>()(val) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}
/**
*	Computes the hash of the concatenated types given the seed.
*/
template<typename FirstArgType, typename... RestArgsType>
INLINE void HashCombine(sizet& seed, const FirstArgType& firstArg, const RestArgsType&... restArgs)
{
	HashCombine(seed, firstArg);
	HashCombine(seed, restArgs...);
}
/**
*	Computes the hash of the concatenated types.
*/
template<typename... ArgsType>
INLINE sizet ComputeHash(const ArgsType&... args)
{
	sizet seed = 0;
	HashCombine(seed, args...);
	return seed;
}

/***********************************************************************************
*                             MEMORY HELPER FUNCITONS                              *
***********************************************************************************/

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))
#endif

#if GREAPER_USE_BASIC_TYPEINFO
template<class T, sizet::Type N>
#else
template<class T, sizet N>
#endif
INLINE constexpr sizet ArraySize(T(&)[N]) noexcept { return N; }

template<class T>
INLINE void ClearMemory(T& obj, sizet count = 1) noexcept
{
	memset(&obj, 0, sizeof(T) * count);
}
template<class T, size_t N>
INLINE void ClearMemory(T(&arr)[N]) noexcept
{
	using Type = std::remove_extent_t<T>;
	memset(&arr[0], 0, sizeof(Type) * N);
}