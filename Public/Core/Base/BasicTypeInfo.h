/***********************************************************************************
*   Copyright 2021 Marcos Sánchez Torrent.                                         *
*   All Rights Reserved.                                                           *
***********************************************************************************/

#pragma once
//#include "../PHAL.h"
#include <memory>

#if GREAPER_USE_BASIC_TYPEINFO
class uint8
{
public:
	using Type = PlatformTypes::uint8_t;

private:
	Type m = 0;

public:
	static constexpr Type MinValue = 0;
	static constexpr Type MaxValue = 255;
	static constexpr PlatformTypes::uint8_t Bytes = 1;
	static constexpr PlatformTypes::uint8_t MaxStringLength = 3;

	constexpr uint8()noexcept = default;
	constexpr uint8(bool val)noexcept : m(static_cast<Type>(val)) {  }
	constexpr uint8(char val)noexcept : m(static_cast<Type>(val)) { }
	constexpr uint8(wchar_t val)noexcept : m(static_cast<Type>(val)) { }
	constexpr uint8(unsigned char val)noexcept : m(static_cast<Type>(val)) { }
	constexpr uint8(short val)noexcept : m(static_cast<Type>(val)) { }
	constexpr uint8(unsigned short val)noexcept : m(static_cast<Type>(val)) { }
	constexpr uint8(int val)noexcept : m(static_cast<Type>(val)) { }
	constexpr uint8(unsigned int val)noexcept : m(static_cast<Type>(val)) { }
	constexpr uint8(PlatformTypes::int64_t val)noexcept :m(static_cast<Type>(val)) { }
	constexpr uint8(PlatformTypes::uint64_t val)noexcept :m(static_cast<Type>(val)) { }
	constexpr uint8(float val)noexcept :m(static_cast<Type>(val)) { }
	constexpr uint8(double val)noexcept :m(static_cast<Type>(val)) { }

	constexpr uint8 operator+(uint8 other)const noexcept { return uint8{m + other.m}; }
	constexpr uint8 operator-(uint8 other)const noexcept { return uint8{m - other.m}; }
	constexpr uint8 operator*(uint8 other)const noexcept { return uint8{m * other.m}; }
	constexpr uint8 operator/(uint8 other)const noexcept { return uint8{m / other.m}; }
	constexpr uint8 operator%(uint8 other)const noexcept { return uint8{m % other.m}; }
	uint8& operator%=(uint8 other)noexcept { m %= other.m; return *this; }
	uint8& operator+=(uint8 other)noexcept { m += other.m; return *this; }
	uint8& operator-=(uint8 other)noexcept { m -= other.m; return *this; }
	uint8& operator*=(uint8 other)noexcept { m *= other.m; return *this; }
	uint8& operator/=(uint8 other)noexcept { m /= other.m; return *this; }

	constexpr bool operator==(uint8 other)const noexcept { return m == other.m; }
	constexpr bool operator!=(uint8 other)const noexcept { return m != other.m; }
	constexpr bool operator<(uint8 other)const noexcept { return m < other.m; }
	constexpr bool operator>(uint8 other)const noexcept { return m > other.m; }
	constexpr bool operator<=(uint8 other)const noexcept { return m <= other.m; }
	constexpr bool operator>=(uint8 other)const noexcept { return m >= other.m; }

	constexpr uint8 operator&(uint8 other)const noexcept { return uint8{m & other.m}; }
	constexpr uint8 operator|(uint8 other)const noexcept { return uint8{m | other.m}; }
	constexpr uint8 operator^(uint8 other)const noexcept { return uint8{m ^ other.m}; }
	constexpr uint8 operator<<(uint8 other)const noexcept { return uint8{m << other.m}; }
	constexpr uint8 operator>>(uint8 other)const noexcept { return uint8{m >> other.m}; }
	uint8& operator&=(uint8 other)noexcept { m &= other.m; return *this; }
	uint8& operator|=(uint8 other)noexcept { m |= other.m; return *this; }
	uint8& operator^=(uint8 other)noexcept { m ^= other.m; return *this; }
	uint8& operator<<=(uint8 other)noexcept { m <<= other.m; return *this; }
	uint8& operator>>=(uint8 other)noexcept { m >>= other.m; return *this; }

	constexpr uint8 operator-()const noexcept { return uint8{-m}; }
	constexpr uint8 operator~()const noexcept { return uint8{~m}; }
	uint8 operator++()noexcept { uint8 temp{m}; ++m; return temp; }
	uint8& operator++(int)noexcept { ++m; return *this; }
	uint8 operator--()noexcept { uint8 temp{m}; --m; return temp; }
	uint8& operator--(int)noexcept { --m; return *this; }

	constexpr Type GetValue()const noexcept { return m; }
};

class u8char
{
public:
	using Type = PlatformTypes::utf8char;

private:
	Type m = 0;

public:
	static constexpr Type MinValue = 0;
	static constexpr Type MaxValue = 255;
	static constexpr PlatformTypes::uint8_t Bytes = 1;
	static constexpr PlatformTypes::uint8_t MaxStringLength = 3;

	constexpr u8char()noexcept = default;
	constexpr u8char(bool val)noexcept : m(static_cast<Type>(val)) {  }
	constexpr u8char(char val)noexcept : m(static_cast<Type>(val)) { }
	constexpr u8char(wchar_t val)noexcept : m(static_cast<Type>(val)) { }
	constexpr u8char(unsigned char val)noexcept : m(static_cast<Type>(val)) { }
	constexpr u8char(short val)noexcept : m(static_cast<Type>(val)) { }
	constexpr u8char(unsigned short val)noexcept : m(static_cast<Type>(val)) { }
	constexpr u8char(int val)noexcept : m(static_cast<Type>(val)) { }
	constexpr u8char(unsigned int val)noexcept : m(static_cast<Type>(val)) { }
	constexpr u8char(PlatformTypes::int64_t val)noexcept :m(static_cast<Type>(val)) { }
	constexpr u8char(PlatformTypes::uint64_t val)noexcept :m(static_cast<Type>(val)) { }
	constexpr u8char(float val)noexcept :m(static_cast<Type>(val)) { }
	constexpr u8char(double val)noexcept :m(static_cast<Type>(val)) { }

	constexpr Type GetValue()const noexcept { return m; }
};

class int8
{
public:
	using Type = PlatformTypes::int8_t;
	 
private:
	Type m = 0;

public:
	static constexpr Type MinValue = -128;
	static constexpr Type MaxValue = 127;
	static constexpr PlatformTypes::uint8_t Bytes = 1;
	static constexpr PlatformTypes::uint8_t MaxStringLength = 4;

	constexpr int8()noexcept = default;
	constexpr int8(bool val)noexcept : m(static_cast<Type>(val)) {  }
	constexpr int8(char val)noexcept : m(static_cast<Type>(val)) { }
	constexpr int8(wchar_t val)noexcept : m(static_cast<Type>(val)) { }
	constexpr int8(unsigned char val)noexcept : m(static_cast<Type>(val)) { }
	constexpr int8(short val)noexcept : m(static_cast<Type>(val)) { }
	constexpr int8(unsigned short val)noexcept : m(static_cast<Type>(val)) { }
	constexpr int8(int val)noexcept : m(static_cast<Type>(val)) { }
	constexpr int8(unsigned int val)noexcept : m(static_cast<Type>(val)) { }
	constexpr int8(PlatformTypes::int64_t val)noexcept :m(static_cast<Type>(val)) { }
	constexpr int8(PlatformTypes::uint64_t val)noexcept :m(static_cast<Type>(val)) { }
	constexpr int8(float val)noexcept :m(static_cast<Type>(val)) { }
	constexpr int8(double val)noexcept :m(static_cast<Type>(val)) { }

	/*template<class T>
	static constexpr T Clamp(T val)noexcept
	{
		return ::Clamp(val, (T)MinValue, (T)MaxValue);
	}*/

	constexpr Type GetValue()const noexcept { return m; }

};

class achar
{
public:
	using Type = PlatformTypes::ansichar;

private:
	Type m = 0;

public:
	static constexpr Type MinValue = -128;
	static constexpr Type MaxValue = 127;
	static constexpr PlatformTypes::uint8_t Bytes = 1;
	static constexpr PlatformTypes::uint8_t MaxStringLength = 4;

	constexpr achar()noexcept = default;
	constexpr achar(bool val)noexcept : m(static_cast<Type>(val)) {  }
	constexpr achar(char val)noexcept : m(static_cast<Type>(val)) { }
	constexpr achar(wchar_t val)noexcept : m(static_cast<Type>(val)) { }
	constexpr achar(unsigned char val)noexcept : m(static_cast<Type>(val)) { }
	constexpr achar(short val)noexcept : m(static_cast<Type>(val)) { }
	constexpr achar(unsigned short val)noexcept : m(static_cast<Type>(val)) { }
	constexpr achar(int val)noexcept : m(static_cast<Type>(val)) { }
	constexpr achar(unsigned int val)noexcept : m(static_cast<Type>(val)) { }
	constexpr achar(PlatformTypes::int64_t val)noexcept :m(static_cast<Type>(val)) { }
	constexpr achar(PlatformTypes::uint64_t val)noexcept :m(static_cast<Type>(val)) { }
	constexpr achar(float val)noexcept :m(static_cast<Type>(val)) { }
	constexpr achar(double val)noexcept :m(static_cast<Type>(val)) { }

	constexpr Type GetValue()const noexcept { return m; }
};

class uint16
{
public:
	using Type = PlatformTypes::uint16_t;

private:
	Type m = 0;

public:
	static constexpr Type MinValue = 0;
	static constexpr Type MaxValue = 0xFFFF;
	static constexpr PlatformTypes::uint8_t Bytes = 2;
	static constexpr PlatformTypes::uint8_t MaxStringLength = 5;

	constexpr uint16()noexcept = default;
	constexpr uint16(bool val)noexcept : m(static_cast<Type>(val)) {  }
	constexpr uint16(char val)noexcept : m(static_cast<Type>(val)) { }
	constexpr uint16(wchar_t val)noexcept : m(val) { }
	constexpr uint16(unsigned char val)noexcept : m(static_cast<Type>(val)) { }
	constexpr uint16(short val)noexcept : m(static_cast<Type>(val)) { }
	constexpr uint16(unsigned short val)noexcept : m(val) { }
	constexpr uint16(int val)noexcept : m(static_cast<Type>(val)) { }
	constexpr uint16(unsigned int val)noexcept : m(static_cast<Type>(val)) { }
	constexpr uint16(PlatformTypes::int64_t val)noexcept :m(static_cast<Type>(val)) { }
	constexpr uint16(PlatformTypes::uint64_t val)noexcept :m(static_cast<Type>(val)) { }
	constexpr uint16(float val)noexcept :m(static_cast<Type>(val)) { }
	constexpr uint16(double val)noexcept :m(static_cast<Type>(val)) { }

	constexpr Type GetValue()const noexcept { return m; }
};

class u16char
{
public:
	using Type = PlatformTypes::utf16char;

private:
	Type m = 0;

public:
	static constexpr Type MinValue = 0;
	static constexpr Type MaxValue = 0xFFFF;
	static constexpr PlatformTypes::uint8_t Bytes = 2;
	static constexpr PlatformTypes::uint8_t MaxStringLength = 5;

	constexpr u16char()noexcept = default;
	constexpr u16char(bool val)noexcept : m(static_cast<Type>(val)) {  }
	constexpr u16char(char val)noexcept : m(static_cast<Type>(val)) { }
	constexpr u16char(wchar_t val)noexcept : m(val) { }
	constexpr u16char(unsigned char val)noexcept : m(static_cast<Type>(val)) { }
	constexpr u16char(short val)noexcept : m(static_cast<Type>(val)) { }
	constexpr u16char(unsigned short val)noexcept : m(val) { }
	constexpr u16char(int val)noexcept : m(static_cast<Type>(val)) { }
	constexpr u16char(unsigned int val)noexcept : m(static_cast<Type>(val)) { }
	constexpr u16char(PlatformTypes::int64_t val)noexcept :m(static_cast<Type>(val)) { }
	constexpr u16char(PlatformTypes::uint64_t val)noexcept :m(static_cast<Type>(val)) { }
	constexpr u16char(float val)noexcept :m(static_cast<Type>(val)) { }
	constexpr u16char(double val)noexcept :m(static_cast<Type>(val)) { }

	constexpr Type GetValue()const noexcept { return m; }
};

class wchar
{
public:
	using Type = PlatformTypes::widechar;

private:
	Type m = 0;

public:
	static constexpr Type MinValue = 0;
	static constexpr Type MaxValue = 0xFFFF;
	static constexpr PlatformTypes::uint8_t Bytes = 2;
	static constexpr PlatformTypes::uint8_t MaxStringLength = 5;

	constexpr wchar()noexcept = default;
	constexpr wchar(bool val)noexcept : m(static_cast<Type>(val)) {  }
	constexpr wchar(char val)noexcept : m(static_cast<Type>(val)) { }
	constexpr wchar(wchar_t val)noexcept : m(val) { }
	constexpr wchar(unsigned char val)noexcept : m(static_cast<Type>(val)) { }
	constexpr wchar(short val)noexcept : m(static_cast<Type>(val)) { }
	constexpr wchar(unsigned short val)noexcept : m(val) { }
	constexpr wchar(int val)noexcept : m(static_cast<Type>(val)) { }
	constexpr wchar(unsigned int val)noexcept : m(static_cast<Type>(val)) { }
	constexpr wchar(PlatformTypes::int64_t val)noexcept :m(static_cast<Type>(val)) { }
	constexpr wchar(PlatformTypes::uint64_t val)noexcept :m(static_cast<Type>(val)) { }
	constexpr wchar(float val)noexcept :m(static_cast<Type>(val)) { }
	constexpr wchar(double val)noexcept :m(static_cast<Type>(val)) { }

	constexpr Type GetValue()const noexcept { return m; }
};

class int16
{
public:
	using Type = PlatformTypes::int16_t;

private:
	Type m = 0;

public:
	static constexpr Type MinValue = -32768;
	static constexpr Type MaxValue = 32767;
	static constexpr PlatformTypes::uint8_t Bytes = 2;
	static constexpr PlatformTypes::uint8_t MaxStringLength = 6;

	constexpr int16()noexcept = default;
	constexpr int16(bool val)noexcept : m(static_cast<Type>(val)) {  }
	constexpr int16(char val)noexcept : m(static_cast<Type>(val)) { }
	constexpr int16(wchar_t val)noexcept : m(static_cast<Type>(val)) { }
	constexpr int16(unsigned char val)noexcept : m(static_cast<Type>(val)) { }
	constexpr int16(short val)noexcept : m(static_cast<Type>(val)) { }
	constexpr int16(unsigned short val)noexcept : m(static_cast<Type>(val)) { }
	constexpr int16(int val)noexcept : m(static_cast<Type>(val)) { }
	constexpr int16(unsigned int val)noexcept : m(static_cast<Type>(val)) { }
	constexpr int16(PlatformTypes::int64_t val)noexcept :m(static_cast<Type>(val)) { }
	constexpr int16(PlatformTypes::uint64_t val)noexcept :m(static_cast<Type>(val)) { }
	constexpr int16(float val)noexcept :m(static_cast<Type>(val)) { }
	constexpr int16(double val)noexcept :m(static_cast<Type>(val)) { }

	constexpr Type GetValue()const noexcept { return m; }
};

class uint32
{
public:
	using Type = PlatformTypes::uint32_t;

private:
	Type m = 0;

public:
	static constexpr Type MinValue = 0;
	static constexpr Type MaxValue = 0xFFFFFFFF;
	static constexpr PlatformTypes::uint8_t Bytes = 4;
	static constexpr PlatformTypes::uint8_t MaxStringLength = 10;

	constexpr uint32()noexcept = default;
	constexpr uint32(bool val)noexcept : m(static_cast<Type>(val)) {  }
	constexpr uint32(char val)noexcept : m(static_cast<Type>(val)) { }
	constexpr uint32(wchar_t val)noexcept : m(static_cast<Type>(val)) { }
	constexpr uint32(unsigned char val)noexcept : m(static_cast<Type>(val)) { }
	constexpr uint32(short val)noexcept : m(static_cast<Type>(val)) { }
	constexpr uint32(unsigned short val)noexcept : m(static_cast<Type>(val)) { }
	constexpr uint32(int val)noexcept : m(static_cast<Type>(val)) { }
	constexpr uint32(unsigned int val)noexcept : m(val) { }
	constexpr uint32(PlatformTypes::int64_t val)noexcept :m(static_cast<Type>(val)) { }
	constexpr uint32(PlatformTypes::uint64_t val)noexcept :m(static_cast<Type>(val)) { }
	constexpr uint32(float val)noexcept :m(static_cast<Type>(val)) { }
	constexpr uint32(double val)noexcept :m(static_cast<Type>(val)) { }

	constexpr Type GetValue()const noexcept { return m; }
};

class u32char
{
public:
	using Type = PlatformTypes::utf32char;

private:
	Type m = 0;

public:
	static constexpr Type MinValue = 0;
	static constexpr Type MaxValue = 0xFFFFFFFF;
	static constexpr PlatformTypes::uint8_t Bytes = 4;
	static constexpr PlatformTypes::uint8_t MaxStringLength = 10;

	constexpr u32char()noexcept = default;
	constexpr u32char(bool val)noexcept : m(static_cast<Type>(val)) {  }
	constexpr u32char(char val)noexcept : m(static_cast<Type>(val)) { }
	constexpr u32char(wchar_t val)noexcept : m(static_cast<Type>(val)) { }
	constexpr u32char(unsigned char val)noexcept : m(static_cast<Type>(val)) { }
	constexpr u32char(short val)noexcept : m(static_cast<Type>(val)) { }
	constexpr u32char(unsigned short val)noexcept : m(static_cast<Type>(val)) { }
	constexpr u32char(int val)noexcept : m(static_cast<Type>(val)) { }
	constexpr u32char(unsigned int val)noexcept : m(val) { }
	constexpr u32char(PlatformTypes::int64_t val)noexcept :m(static_cast<Type>(val)) { }
	constexpr u32char(PlatformTypes::uint64_t val)noexcept :m(static_cast<Type>(val)) { }
	constexpr u32char(float val)noexcept :m(static_cast<Type>(val)) { }
	constexpr u32char(double val)noexcept :m(static_cast<Type>(val)) { }

	constexpr Type GetValue()const noexcept { return m; }
};

class int32
{
public:
	using Type = PlatformTypes::uint32_t;

private:
	Type m = 0;

public:
	static constexpr Type MinValue = -2147483648;
	static constexpr Type MaxValue = 2147483647;
	static constexpr PlatformTypes::uint8_t Bytes = 4;
	static constexpr PlatformTypes::uint8_t MaxStringLength = 11;

	constexpr int32()noexcept = default;
	constexpr int32(bool val)noexcept : m(static_cast<Type>(val)) {  }
	constexpr int32(char val)noexcept : m(static_cast<Type>(val)) { }
	constexpr int32(wchar_t val)noexcept : m(static_cast<Type>(val)) { }
	constexpr int32(unsigned char val)noexcept : m(static_cast<Type>(val)) { }
	constexpr int32(short val)noexcept : m(static_cast<Type>(val)) { }
	constexpr int32(unsigned short val)noexcept : m(static_cast<Type>(val)) { }
	constexpr int32(int val)noexcept : m(val) { }
	constexpr int32(unsigned int val)noexcept : m(static_cast<Type>(val)) { }
	constexpr int32(PlatformTypes::int64_t val)noexcept :m(static_cast<Type>(val)) { }
	constexpr int32(PlatformTypes::uint64_t val)noexcept :m(static_cast<Type>(val)) { }
	constexpr int32(float val)noexcept :m(static_cast<Type>(val)) { }
	constexpr int32(double val)noexcept :m(static_cast<Type>(val)) { }

	constexpr Type GetValue()const noexcept { return m; }
};

class uint64
{
public:
	using Type = PlatformTypes::uint64_t;

private:
	Type m = 0;

public:
	static constexpr Type MinValue = 0;
	static constexpr Type MaxValue = 0xFFFFFFFFFFFFFFFF;
	static constexpr PlatformTypes::uint8_t Bytes = 8;
	static constexpr PlatformTypes::uint8_t MaxStringLength = 20;

	constexpr uint64()noexcept = default;
	constexpr uint64(bool val)noexcept : m(static_cast<Type>(val)) {  }
	constexpr uint64(char val)noexcept : m(static_cast<Type>(val)) { }
	constexpr uint64(wchar_t val)noexcept : m(static_cast<Type>(val)) { }
	constexpr uint64(unsigned char val)noexcept : m(static_cast<Type>(val)) { }
	constexpr uint64(short val)noexcept : m(static_cast<Type>(val)) { }
	constexpr uint64(unsigned short val)noexcept : m(static_cast<Type>(val)) { }
	constexpr uint64(int val)noexcept : m(static_cast<Type>(val)) { }
	constexpr uint64(unsigned int val)noexcept : m(static_cast<Type>(val)) { }
	constexpr uint64(PlatformTypes::int64_t val)noexcept :m(static_cast<Type>(val)) { }
	constexpr uint64(PlatformTypes::uint64_t val)noexcept :m(static_cast<Type>(val)) { }
	constexpr uint64(float val)noexcept :m(static_cast<Type>(val)) { }
	constexpr uint64(double val)noexcept :m(static_cast<Type>(val)) { }

	constexpr Type GetValue()const noexcept { return m; }
};

class int64
{
public:
	using Type = PlatformTypes::int64_t;

private:
	Type m = 0;

public:
	static constexpr Type MinValue = -9223372036854775808;
	static constexpr Type MaxValue = 9223372036854775807;
	static constexpr PlatformTypes::uint8_t Bytes = 8;
	static constexpr PlatformTypes::uint8_t MaxStringLength = 20;

	constexpr int64()noexcept = default;
	constexpr int64(bool val)noexcept : m(static_cast<Type>(val)) {  }
	constexpr int64(char val)noexcept : m(static_cast<Type>(val)) { }
	constexpr int64(wchar_t val)noexcept : m(static_cast<Type>(val)) { }
	constexpr int64(unsigned char val)noexcept : m(static_cast<Type>(val)) { }
	constexpr int64(short val)noexcept : m(static_cast<Type>(val)) { }
	constexpr int64(unsigned short val)noexcept : m(static_cast<Type>(val)) { }
	constexpr int64(int val)noexcept : m(static_cast<Type>(val)) { }
	constexpr int64(unsigned int val)noexcept : m(static_cast<Type>(val)) { }
	constexpr int64(PlatformTypes::int64_t val)noexcept :m(static_cast<Type>(val)) { }
	constexpr int64(PlatformTypes::uint64_t val)noexcept :m(static_cast<Type>(val)) { }
	constexpr int64(float val)noexcept :m(static_cast<Type>(val)) { }
	constexpr int64(double val)noexcept :m(static_cast<Type>(val)) { }

	constexpr Type GetValue()const noexcept { return m; }
};

class f32
{
public:
	using Type = float;

private:
	Type m = 0;

public:
	static constexpr Type MinValue = 1.175494351e-38F;
	static constexpr Type MaxValue = 3.402823466e+38F;
	static constexpr PlatformTypes::uint8_t Bytes = 4;
	static constexpr PlatformTypes::uint8_t MaxStringLength = 16;

	constexpr f32()noexcept = default;
	constexpr f32(bool val)noexcept : m(static_cast<Type>(val)) {  }
	constexpr f32(char val)noexcept : m(static_cast<Type>(val)) { }
	constexpr f32(wchar_t val)noexcept : m(static_cast<Type>(val)) { }
	constexpr f32(unsigned char val)noexcept : m(static_cast<Type>(val)) { }
	constexpr f32(short val)noexcept : m(static_cast<Type>(val)) { }
	constexpr f32(unsigned short val)noexcept : m(static_cast<Type>(val)) { }
	constexpr f32(int val)noexcept : m(static_cast<Type>(val)) { }
	constexpr f32(unsigned int val)noexcept : m(static_cast<Type>(val)) { }
	constexpr f32(PlatformTypes::int64_t val)noexcept :m(static_cast<Type>(val)) { }
	constexpr f32(PlatformTypes::uint64_t val)noexcept :m(static_cast<Type>(val)) { }
	constexpr f32(float val)noexcept :m(static_cast<Type>(val)) { }
	constexpr f32(double val)noexcept :m(static_cast<Type>(val)) { }

	constexpr Type GetValue()const noexcept { return m; }
};

class f64
{
public:
	using Type = double;

private:
	Type m = 0;

public:
	static constexpr Type MinValue = 2.2250738585072014e-308;
	static constexpr Type MaxValue = 1.7976931348623158e+308;
	static constexpr PlatformTypes::uint8_t Bytes = 8;
	static constexpr PlatformTypes::uint8_t MaxStringLength = 23;

	constexpr f64()noexcept = default;
	constexpr f64(bool val)noexcept : m(static_cast<Type>(val)) {  }
	constexpr f64(char val)noexcept : m(static_cast<Type>(val)) { }
	constexpr f64(wchar_t val)noexcept : m(static_cast<Type>(val)) { }
	constexpr f64(unsigned char val)noexcept : m(static_cast<Type>(val)) { }
	constexpr f64(short val)noexcept : m(static_cast<Type>(val)) { }
	constexpr f64(unsigned short val)noexcept : m(static_cast<Type>(val)) { }
	constexpr f64(int val)noexcept : m(static_cast<Type>(val)) { }
	constexpr f64(unsigned int val)noexcept : m(static_cast<Type>(val)) { }
	constexpr f64(PlatformTypes::int64_t val)noexcept :m(static_cast<Type>(val)) { }
	constexpr f64(PlatformTypes::uint64_t val)noexcept :m(static_cast<Type>(val)) { }
	constexpr f64(float val)noexcept :m(static_cast<Type>(val)) { }
	constexpr f64(double val)noexcept :m(static_cast<Type>(val)) { }

	constexpr Type GetValue()const noexcept { return m; }
};

using sizet = uint64;
using ssizet = int64;
using ptruint = sizet;
using ptrint = ssizet;
#else
using uint8 = PlatformTypes::uint8_t;
using uint16 = PlatformTypes::uint16_t;
using uint32 = PlatformTypes::uint32_t;
using uint64 = PlatformTypes::uint64_t;
using int8 = PlatformTypes::int8_t;
using int16 = PlatformTypes::int16_t;
using int32 = PlatformTypes::int32_t;
using int64 = PlatformTypes::int64_t;
using achar = PlatformTypes::ansichar;
using wchar = PlatformTypes::widechar;
using u8char = PlatformTypes::utf8char;
using u16char = PlatformTypes::utf16char;
using u32char = PlatformTypes::utf32char;
using ptruint = PlatformTypes::ptruint_t;
using ptrint = PlatformTypes::ptrint_t;
using sizet = PlatformTypes::sizetype;
using ssizet = PlatformTypes::ssizetype;
#endif

template<class T>
using SPtr = std::shared_ptr<T>;
template<class T>
using UPtr = std::unique_ptr<T>;