/***********************************************************************************
*   Copyright 2021 Marcos Sánchez Torrent.                                         *
*   All Rights Reserved.                                                           *
***********************************************************************************/

#pragma once

#ifndef GREAPER_CORE_STRING_UTILS_H
#define GREAPER_CORE_STRING_UTILS_H 1

#include "PHAL.h"
#include "Memory.h"
#include <iterator>

namespace greaper::StringUtils
{
	namespace Impl
	{
		template<typename T>
		T UTF8To32(T begin, T end, u32char& output, u32char invalidChar = 0)
		{
			if (begin >= end)
				return begin;

			static constexpr uint32 offsets[6] = { 0x00000000, 0x00003080, 0x000E2080, 0x03C82080, 0xFA082080, 0x82082080 };

			uint32 numBytes = 0;

			const auto firstByte = (uint8)*begin;
			if (firstByte < 192)
				numBytes = 1;
			else if (firstByte < 224)
				numBytes = 2;
			else if (firstByte < 240)
				numBytes = 3;
			else if (firstByte < 248)
				numBytes = 4;
			else if (firstByte < 252)
				numBytes = 5;
			else
				numBytes = 6;

			if ((begin + numBytes) > end)
			{
				output = invalidChar;
				return end;
			}

			output = 0;
			switch (numBytes)
			{
				case 6: output += (uint8)(*begin); ++begin; output <<= 6;
				case 5: output += (uint8)(*begin); ++begin; output <<= 6;
				case 4: output += (uint8)(*begin); ++begin; output <<= 6;
				case 3: output += (uint8)(*begin); ++begin; output <<= 6;
				case 2: output += (uint8)(*begin); ++begin; output <<= 6;
				case 1: output += (uint8)(*begin); ++begin;
				default: break;
			}
			output -= offsets[numBytes - 1];
			return begin;
		}

		template<typename T>
		T UTF32To8(u32char input, T output, uint32 maxElems, achar invalidChar = 0)
		{
			if (maxElems == 0)
				return output;
			
			static constexpr uint8 headers[7] = { 0x00, 0x00, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC };

			if ((input > 0x0010FFFF) || ((input >= 0xD800) && (input <= 0xDBFF)))
			{
				*output = invalidChar;
				++output;
				return output;
			}

			uint32 numBytes = 0;;
			if (input < 0x80)
				numBytes = 1;
			else if (input < 0x800)
				numBytes = 2;
			else if (input < 0x10000)
				numBytes = 3;
			else
				numBytes = 4;

			if (numBytes > maxElems)
			{
				*output = invalidChar;
				++output;
				return output;
			}

			achar bytes[4];
			switch (numBytes)
			{
				case 4: bytes[3] = (achar)((input | 0x80) & 0xBF); input >>= 6;
				case 3: bytes[2] = (achar)((input | 0x80) & 0xBF); input >>= 6;
				case 2: bytes[1] = (achar)((input | 0x80) & 0xBF); input >>= 6;
				case 1: bytes[0] = (achar)(input | headers[numBytes]);
				default: break;
			}

			output = std::copy(bytes, bytes + numBytes, output);
			return output;
		}

		template<typename T>
		T UTF16To32(T begin, T end, u32char& output, u32char invalidChar = 0)
		{
			if (begin >= end)
				return begin;

			const auto firstElem = (char16)*begin;
			++begin;

			if ((firstElem >= 0xD800) && (firstElem <= 0xDBFF))
			{
				if (begin >= end)
				{
					output = invalidChar;
					return end;
				}

				const auto secondElem = (char32)*begin;
				++begin;

				if ((secondElem >= 0xDC00) && (secondElem <= 0xDFFF))
					output = (char32)(((firstElem - 0xD800) << 10) + (secondElem - 0xDC00) + 0x0010000);
				else
					output = invalidChar;
			}
			else
			{
				output = (char32)firstElem;
				return begin;
			}
			return begin;
		}

		template<typename T>
		T WIDEToUTF32(T begin, T end, u32char& output, u32char invalidChar = 0)
		{
#if PLT_LINUX
			output = (char32)*begin;
			++begin;
			return begin;
#else
			return UTF16To32(begin, end, output, invalidChar);
#endif
		}

		template<typename T>
		T UTF32ToWIDE(u32char input, T output, uint32 maxElems, wchar invalidChar = 0)
		{
#if PLT_LINUX
			* output = (wchar)input;
			++output;

			return output;
#else
			return UTF32To16(input, output, maxElems, invalidChar);
#endif
		}

		template<typename T>
		struct CaseImpl
		{
			int(*Lower)(int C) = &::tolower;
			int(*Upper)(int C) = &::toupper;
		};

		template<>
		struct CaseImpl<achar>
		{
			int(*Lower)(int C) = &::tolower;
			int(*Upper)(int C) = &::toupper;
		};

		template<>
		struct CaseImpl<wchar>
		{
			wint_t(*Lower)(wint_t c) = &::towlower;
			wint_t(*Upper)(wint_t c) = &::towupper;
		};
	}

	template<class _Alloca_ = StdAlloc<achar>, class _Allocw_ = StdAlloc<wchar>>
	BasicString<achar, _Alloca_> FromWIDE(const BasicString<wchar, _Allocw_>& str)
	{
		std::basic_string<achar, std::char_traits<achar>, _Alloca_> output;
		output.reserve(str.size());

		auto backInserter = std::back_inserter(output);

		for (auto it = str.begin(); it != str.end();)
		{
			char32 c32 = 0;
			it = Impl::WIDEToUTF32(it, str.end() c32);
			Impl::UTF32To8(c32, backInserter, 4);
		}
	}

	template<class _Allocw_ = StdAlloc<wchar>, class _Alloca_ = StdAlloc<achar>>
	BasicString<wchar, _Allocw_> ToWIDE(const BasicString<achar, _Alloca_>& str)
	{
		std::basic_string<wchar, std::char_traits<wchar>, _Allocw_> output;
		output.reserve(str.size());

		auto backInserter = std::back_inserter(output);

		for (auto it = str.begin(); it != str.end(); )
		{
			char32 c32 = 0;
			it = Impl::UTF8To32(it, str.end(), c32);
			Impl::UTF32ToWIDE(c32, backInserter, 2);

		}

		return output;
	}

	template<typename T, class _Alloca_ = StdAlloc<T>>
	sizet Contains(const BasicString<T, _Alloca_>& str, T token)
	{
		sizet count = 0;
		for (const T c : str)
		{
			if (c == token)
				++count;
		}
		return count;
	}

	template<typename T, class _Alloca_ = StdAlloc<T>>
	sizet Contains(const BasicString<T, _Alloca_>& str, const BasicString<T, _Alloca_>& token)
	{
		sizet count = 0;
		for (auto it = str.begin(); it != str.end(); ++it)
		{
			auto itt = it;
			bool match = true;
			for (auto ittt = token.begin(); ittt != token.end(); ++ittt)
			{
				if ((*itt) != (*ittt))
				{
					match = false;
					break;
				}
				++itt;
			}
			if (match)
				++count;
		}
		return count;
	}

	template<typename T, class _Alloca_ = StdAlloc<T>, class _VAlloca_ = StdAlloc<BasicString<T, _Alloca_>>>
	BasicString<T, _Alloca_> ComposeString(const std::vector<BasicString<T, _Alloca_>, _VAlloca_>& vec, T separator)
	{
		BasicString<T, _Alloca_> rtn;
		for (sizet i = 0; i < vec.size(); ++i)
		{
			rtn += vec[i];
			if (i != (vec.size() - 1))
				rtn += separator;
		}

		return rtn;
	}

	template<typename T, class _Alloca_ = StdAlloc<T>, class _VAlloca_ = StdAlloc<BasicString<T, _Alloca_>>>
	BasicString<T, _Alloca_> ComposeString(const std::vector<BasicString<T, _Alloca_>, _VAlloca_>& vec,
		const BasicString<T, _Alloca_>& separator)
	{
		BasicString<T, _Alloca_> rtn;
		for (sizet i = 0; i < vec.size(); ++i)
		{
			rtn += vec[i];
			if (i != (vec.size() - 1))
				rtn += separator;
		}
		return rtn;
	}

	template<typename T, class _Alloca_ = StdAlloc<T>, class _VAlloca_ = StdAlloc<BasicString<T, _Alloca_>>>
	std::vector<BasicString<T, _Alloca_>, _VAlloca_> Tokenize(const BasicString<T, _Alloca_>& str, T token)
	{
		std::vector<BasicString<T, _Alloca_>, _VAlloca_> rtn;
		if (str.empty())
			return rtn;
		auto lastToken = str.begin();
		for (auto it = str.begin(); it != str.end(); ++it)
		{
			if ((*it) == token)
			{
				rtn.emplace_back(str.substr(std::distance(str.begin(), lastToken), std::distance(lastToken, it)));
				lastToken = it;
				++lastToken;
			}
		}
		rtn.push_back(BasicString<T, _Alloca_>(lastToken, str.end()));
		return rtn;
	}

	template<typename T, class _Alloca_ = StdAlloc<T>, class _VAlloca_ = StdAlloc<BasicString<T, _Alloca_>>>
	std::vector<BasicString<T, _Alloca_>, _VAlloca_> Tokenize(const BasicString<T, _Alloca_>& str,
		const BasicString<T, _Alloca_>& token)
	{
		std::vector<BasicString<T, _Alloca_>, _VAlloca_> rtn;
		if (str.empty())
			return rtn;
		auto lastToken = str.begin();
		const size_t tokenSize = token.size();
		for (auto it = str.begin(); it != str.end(); ++it)
		{
			if (static_cast<size_t>(std::distance(it, str.end())) < tokenSize)
			{
				rtn.emplace_back(str.substr(std::distance(str.begin(), lastToken)));
				break;
			}
			auto itt = it;
			bool match = true;
			for (auto ittt = token.begin(); ittt != token.end(); ++ittt)
			{
				if ((*itt) != (*ittt))
				{
					match = false;
					break;
				}
				++itt;
			}
			if (match)
			{
				rtn.emplace_back(str.substr(std::distance(str.begin(), lastToken), tokenSize));
				it += tokenSize;
			}
		}
		rtn.push_back(BasicString<T, _Alloca_>(lastToken, str.end()));
		return rtn;
	}

	template<typename T, class _Alloca_ = StdAlloc<T>, class _VAlloca_ = StdAlloc<BasicString<T, _Alloca_>>>
	std::vector<BasicString<T, _Alloca_>, _VAlloca_> SeparateBySpace(const BasicString<T, _Alloca_>& str)
	{
		return Tokenize(str, T(' '));
	}

	template<typename T, class _Alloca_ = StdAlloc<T>>
	BasicString<T, _Alloca_>& Trim(BasicString<T, _Alloca_>& str, const std::basic_string<T,
		std::char_traits<T>, _Alloca_>& delims, bool left = true, bool right = true)
	{
		if (right)
			str.erase(str.find_last_not_of(delims) + 1);
		if (left)
			str.erase(str.find_first_not_of(delims));
		return str;
	}

	template<typename T, class _Alloca_ = StdAlloc<T>>
	BasicString<T, _Alloca_>& Trim(BasicString<T, _Alloca_>& str, bool left = true, bool right = true)
	{
		static const T delims[] = { T(' '), T('\t'), T('\r'), T('\000') };
		return Trim(str, BasicString<T, _Alloca_>(&delims[0]), left, right);
	}

	template<typename T, class _Alloca_ = StdAlloc<T>>
	BasicString<T, _Alloca_> Replace(const BasicString<T, _Alloca_>& str, T toReplace, T replacement)
	{
		return ComposeString(Tokenize(str, toReplace), replacement);
	}

	template<typename T, class _Alloca_ = StdAlloc<T>>
	BasicString<T, _Alloca_> Replace(const BasicString<T, _Alloca_>& str,
		const BasicString<T, _Alloca_>& toReplace, const BasicString<T, _Alloca_>& replacement)
	{
		return ComposeString(Tokenize(str, toReplace), replacement);
	}

	template<typename T, class _Alloca_ = StdAlloc<T>>
	BasicString<T, _Alloca_>& ToLowerSelf(BasicString<T, _Alloca_>& str)
	{
		Impl::CaseImpl<T> caseTransform;
		for (T& c : str)
			c = (T)caseTransform.Lower(c);
		return str;
	}

	template<typename T, class _Alloca_ = StdAlloc<T>>
	BasicString<T, _Alloca_> ToLower(const BasicString<T, _Alloca_>& str)
	{
		BasicString<T, _Alloca_> tmp{str};
		ToLowerSelf(tmp);
		return tmp;
	}

	template<typename T, class _Alloca_ = StdAlloc<T>>
	BasicString<T, _Alloca_>& ToUpperSelf(BasicString<T, _Alloca_>& str)
	{
		Impl::CaseImpl<T> caseTransform;
		for (T& c : str)
			c = (T)caseTransform.Upper(c);
		return str;
	}

	template<typename T, class _Alloca_ = StdAlloc<T>>
	BasicString<T, _Alloca_> ToUpper(const BasicString<T, _Alloca_>& str)
	{
		BasicString<T, _Alloca_> tmp{str};
		ToUpperSelf(tmp);
		return tmp;
	}

	template<typename T, class _Alloca_ = StdAlloc<T>>
	bool StringNumber(const BasicString<T, _Alloca_>& str)
	{
		for (auto& chr : str)
		{
			if (!IsWithinInclusive(chr, T('0'), T('9'))/* && chr != T('.') && chr != T('+') && chr != T('-') && chr != T('e') && chr != T('E')*/)
				return false;
		}
		return true;
	}
}

#endif /* GREAPER_CORE_STRING_UTILS_H */