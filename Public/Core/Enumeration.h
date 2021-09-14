/***********************************************************************************
*   Copyright 2021 Marcos Sánchez Torrent.                                         *
*   All Rights Reserved.                                                           *
***********************************************************************************/

#pragma once

#ifndef CORE_ENUMERATION_H
#define CORE_ENUMERATION_H 1

#include "Memory.h"

#define _ENUMDEF_BEGIN(name)\
namespace E##name {

#define _ENUMDEF_END(name)\
}\
using name##_t = E##name::Type;

#define _ENUMDEF_LUT_BEGIN()\
static constexpr const greaper::StringView _LUT[Type::COUNT] = {

#define _ENUMDEF_TOSTRING()\
INLINE constexpr greaper::StringView ToString(Type type)noexcept \
{ \
	return _LUT[static_cast<sizet>(type)]; \
}

#define _ENUMDEF_FROMSTRING()\
INLINE constexpr Type FromString(const greaper::StringView& type)noexcept \
{ \
	for(sizet i = 0; i < ArraySize(_LUT); ++i) \
	{ \
		if(type.size() != _LUT[i].size()) \
			continue; \
		bool found = true; \
		for(sizet j = 0; j < _LUT[i].size(); ++j) \
		{ \
			if(type[j] != _LUT[i][j]) \
			{ \
				found = false; \
				break; \
			} \
		} \
		if(found) \
			return static_cast<Type>(i); \
	} \
	return Type::COUNT; \
}

#define _ENUMDEF_ENUM_BEGIN()\
	enum Type {

#define _ENUMDEF_ENUMLUT_END()\
	};

#define ENUMERATION1(name, val0)			\
_ENUMDEF_BEGIN(name)						\
_ENUMDEF_ENUM_BEGIN()						\
val0,										\
COUNT,										\
_ENUMDEF_ENUMLUT_END()							\
_ENUMDEF_LUT_BEGIN()						\
#val0,										\
_ENUMDEF_ENUMLUT_END()						\
_ENUMDEF_TOSTRING()							\
_ENUMDEF_FROMSTRING()						\
_ENUMDEF_END(name)

#define ENUMERATION2(name, val0, val1)			\
_ENUMDEF_BEGIN(name)						\
_ENUMDEF_ENUM_BEGIN()						\
val0, val1,										\
COUNT,										\
_ENUMDEF_ENUMLUT_END()							\
_ENUMDEF_LUT_BEGIN()						\
#val0, #val1,										\
_ENUMDEF_ENUMLUT_END()						\
_ENUMDEF_TOSTRING()							\
_ENUMDEF_FROMSTRING()						\
_ENUMDEF_END(name)

#define ENUMERATION3(name, val0, val1, val2)			\
_ENUMDEF_BEGIN(name)						\
_ENUMDEF_ENUM_BEGIN()						\
val0, val1, val2,										\
COUNT,										\
_ENUMDEF_ENUMLUT_END()							\
_ENUMDEF_LUT_BEGIN()						\
#val0, #val1, #val2,										\
_ENUMDEF_ENUMLUT_END()						\
_ENUMDEF_TOSTRING()							\
_ENUMDEF_FROMSTRING()						\
_ENUMDEF_END(name)

#define ENUMERATION4(name, val0, val1, val2, val3)			\
_ENUMDEF_BEGIN(name)						\
_ENUMDEF_ENUM_BEGIN()						\
val0, val1, val2, val3,										\
COUNT,										\
_ENUMDEF_ENUMLUT_END()							\
_ENUMDEF_LUT_BEGIN()						\
#val0, #val1, #val2, #val3,										\
_ENUMDEF_ENUMLUT_END()						\
_ENUMDEF_TOSTRING()							\
_ENUMDEF_FROMSTRING()						\
_ENUMDEF_END(name)

#define ENUMERATION5(name, val0, val1, val2, val3, val4)			\
_ENUMDEF_BEGIN(name)						\
_ENUMDEF_ENUM_BEGIN()						\
val0, val1, val2, val3,	val4,									\
COUNT,										\
_ENUMDEF_ENUMLUT_END()							\
_ENUMDEF_LUT_BEGIN()						\
#val0, #val1, #val2, #val3, #val4,										\
_ENUMDEF_ENUMLUT_END()						\
_ENUMDEF_TOSTRING()							\
_ENUMDEF_FROMSTRING()						\
_ENUMDEF_END(name)

#define ENUMERATION6(name, val0, val1, val2, val3, val4, val5)			\
_ENUMDEF_BEGIN(name)						\
_ENUMDEF_ENUM_BEGIN()						\
val0, val1, val2, val3,	val4, val5,									\
COUNT,										\
_ENUMDEF_ENUMLUT_END()							\
_ENUMDEF_LUT_BEGIN()						\
#val0, #val1, #val2, #val3, #val4, #val5,										\
_ENUMDEF_ENUMLUT_END()						\
_ENUMDEF_TOSTRING()							\
_ENUMDEF_FROMSTRING()						\
_ENUMDEF_END(name)

#define ENUMERATION7(name, val0, val1, val2, val3, val4, val5, val6)			\
_ENUMDEF_BEGIN(name)						\
_ENUMDEF_ENUM_BEGIN()						\
val0, val1, val2, val3,	val4, val5, val6,									\
COUNT,										\
_ENUMDEF_ENUMLUT_END()							\
_ENUMDEF_LUT_BEGIN()						\
#val0, #val1, #val2, #val3, #val4, #val5, #val6,										\
_ENUMDEF_ENUMLUT_END()						\
_ENUMDEF_TOSTRING()							\
_ENUMDEF_FROMSTRING()						\
_ENUMDEF_END(name)

#define ENUMERATION8(name, val0, val1, val2, val3, val4, val5, val6, val7)			\
_ENUMDEF_BEGIN(name)						\
_ENUMDEF_ENUM_BEGIN()						\
val0, val1, val2, val3,	val4, val5, val6, val7,									\
COUNT,										\
_ENUMDEF_ENUMLUT_END()							\
_ENUMDEF_LUT_BEGIN()						\
#val0, #val1, #val2, #val3, #val4, #val5, #val6, #val7,										\
_ENUMDEF_ENUMLUT_END()						\
_ENUMDEF_TOSTRING()							\
_ENUMDEF_FROMSTRING()						\
_ENUMDEF_END(name)


#define ENUMERATION9(name, val0, val1, val2, val3, val4, val5, val6, val7, val8)			\
_ENUMDEF_BEGIN(name)						\
_ENUMDEF_ENUM_BEGIN()						\
val0, val1, val2, val3,	val4, val5, val6, val7, val8,									\
COUNT,										\
_ENUMDEF_ENUMLUT_END()							\
_ENUMDEF_LUT_BEGIN()						\
#val0, #val1, #val2, #val3, #val4, #val5, #val6, #val7, #val8,										\
_ENUMDEF_ENUMLUT_END()						\
_ENUMDEF_TOSTRING()							\
_ENUMDEF_FROMSTRING()						\
_ENUMDEF_END(name)

#define ENUMERATION10(name, val0, val1, val2, val3, val4, val5, val6, val7, val8, val9)			\
_ENUMDEF_BEGIN(name)						\
_ENUMDEF_ENUM_BEGIN()						\
val0, val1, val2, val3,	val4, val5, val6, val7, val8, val9,									\
COUNT,										\
_ENUMDEF_ENUMLUT_END()							\
_ENUMDEF_LUT_BEGIN()						\
#val0, #val1, #val2, #val3, #val4, #val5, #val6, #val7, #val8, #val9,										\
_ENUMDEF_ENUMLUT_END()						\
_ENUMDEF_TOSTRING()							\
_ENUMDEF_FROMSTRING()						\
_ENUMDEF_END(name)

#define ENUMERATION11(name, val0, val1, val2, val3, val4, val5, val6, val7, val8, val9, val10)			\
_ENUMDEF_BEGIN(name)						\
_ENUMDEF_ENUM_BEGIN()						\
val0, val1, val2, val3,	val4, val5, val6, val7, val8, val9, val10,									\
COUNT,										\
_ENUMDEF_ENUMLUT_END()							\
_ENUMDEF_LUT_BEGIN()						\
#val0, #val1, #val2, #val3, #val4, #val5, #val6, #val7, #val8, #val9, #val10,										\
_ENUMDEF_ENUMLUT_END()						\
_ENUMDEF_TOSTRING()							\
_ENUMDEF_FROMSTRING()						\
_ENUMDEF_END(name)

#define ENUMERATION12(name, val0, val1, val2, val3, val4, val5, val6, val7, val8, val9, val10, val11)			\
_ENUMDEF_BEGIN(name)						\
_ENUMDEF_ENUM_BEGIN()						\
val0, val1, val2, val3,	val4, val5, val6, val7, val8, val9, val10, val11,									\
COUNT,										\
_ENUMDEF_ENUMLUT_END()							\
_ENUMDEF_LUT_BEGIN()						\
#val0, #val1, #val2, #val3, #val4, #val5, #val6, #val7, #val8, #val9, #val10, #val11,										\
_ENUMDEF_ENUMLUT_END()						\
_ENUMDEF_TOSTRING()							\
_ENUMDEF_FROMSTRING()						\
_ENUMDEF_END(name)

#endif /* CORE_ENUMERATION_H */