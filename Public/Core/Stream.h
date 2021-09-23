/***********************************************************************************
*   Copyright 2021 Marcos S�nchez Torrent.                                         *
*   All Rights Reserved.                                                           *
***********************************************************************************/

#pragma once

#ifndef CORE_STREAM_H
#define CORE_STREAM_H 1

#include "Memory.h"
#include "Enumeration.h"

namespace greaper
{
	ENUMERATION(StringEncoding, UTF8, UTF16);
	class IStream
	{
	public:
		enum AccessMode
		{
			READ = 1,
			WRITE
		};

	protected:
		static constexpr uint32 StreamTempSize = 128;
		String m_Name;
		ssizet m_Size;
		uint16 m_Access;

	public:
		IStream(uint16 accessMode = READ);
		IStream(const String& name, uint16 accessMode = READ);

		virtual ~IStream() = default;

		const String& GetName()const noexcept { return m_Name; }

		uint16 GetAccessMode()const noexcept { return m_Access; }
		
		virtual bool IsReadable()const noexcept;

		virtual bool IsWritable()const noexcept;

		virtual bool IsFile()const noexcept = 0;

		template<typename T>
		IStream& operator>>(T& val);

		virtual ssizet Read(void* buff, ssizet count) = 0;
		
		virtual ssizet Write(const void* buff, ssizet count) = 0;

		virtual ssizet ReadBytes(uint8* data, ssizet count);
		
		virtual	ssizet WriteBytes(const uint8* data, ssizet count);
		
		virtual void WriteString(const String& string, StringEncoding_t encoding = StringEncoding_t::UTF8);
		
		virtual void WriteString(const WString& string, StringEncoding_t encoding = StringEncoding_t::UTF8);

		virtual String GetAsString();

		virtual WString GetAsStringW();

		virtual void Skip(ssizet count) = 0;

		virtual void Seek(ssizet pos) = 0;

		virtual ssizet Tell()const = 0;

		virtual void Align(uint32 count = 1);

		virtual bool Eof()const = 0;

		ssizet Size()const noexcept;

		virtual SPtr<IStream> Clone(bool copyData = true)const = 0;

		virtual void Close() = 0;
	};

}

#endif /* CORE_STREAM_H */