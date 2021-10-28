/***********************************************************************************
*   Copyright 2021 Marcos S�nchez Torrent.                                         *
*   All Rights Reserved.                                                           *
***********************************************************************************/

#include "../MemoryStream.h"

namespace greaper
{
	void MemoryStream::Realloc(const sizet bytes)
	{
		if (bytes == m_Size)
			return;

		VerifyGreater(bytes, m_Size, "Realloc should always increase the size of the MemoryStream.");

		auto* buffer = (uint8*)Alloc(bytes);
		if (m_Data != nullptr)
		{
			m_Cursor = buffer + (m_Cursor - m_Data);
			m_End = buffer + (m_End - m_Data);

			memcpy(buffer, m_Data, m_Size);
			Dealloc(m_Data);
		}
		else
		{
			m_Cursor = buffer;
			m_End = buffer;
		}

		m_Data = buffer;
		m_Size = bytes;
	}

	MemoryStream::MemoryStream()
		:IStream(READ | WRITE)
		,m_Data(nullptr)
		,m_Cursor(nullptr)
		,m_End(nullptr)
		,m_OwnsMemory(true)
	{

	}

	MemoryStream::MemoryStream(const sizet capacity)
		:IStream(READ | WRITE)
		, m_Data(nullptr)
		, m_Cursor(nullptr)
		, m_End(nullptr)
		, m_OwnsMemory(true)
	{
		Realloc(capacity);
		m_End = m_Cursor + capacity;
	}

	MemoryStream::MemoryStream(void* memory, const sizet size)
		:IStream(READ | WRITE)
		, m_Data((uint8*)memory)
		, m_Cursor((uint8*)memory)
		, m_End((uint8*)memory + size)
		, m_OwnsMemory(false)
	{
		m_Size = size;
	}

	MemoryStream::MemoryStream(const MemoryStream& other)
		:IStream(READ | WRITE)
		, m_Data(nullptr)
		, m_Cursor(nullptr)
		, m_End(nullptr)
		, m_OwnsMemory(true)
	{
		m_Size = other.Size();
		m_Data = m_Cursor = (uint8*)Alloc(m_Size);
		m_End = m_Data + (other.m_End - other.m_Data);
		VerifyGreater(m_End, m_Cursor, "Cursor outside of bounds.");
	}

	MemoryStream& MemoryStream::operator=(const MemoryStream& other)
	{
		if (this != &other)
		{
			m_Name = other.m_Name;
			if (m_Data && m_OwnsMemory)
				Dealloc(m_Data);
			if (other.m_OwnsMemory)
			{
				m_Size = 0;
				m_Data = m_Cursor = m_End = nullptr;
				m_OwnsMemory = true;

				Realloc(other.m_Size);
				m_End = m_Data + m_Size;
				m_Cursor = m_Data + (other.m_Cursor - other.m_Data);

				if (m_Size > 0)
					memcpy(m_Data, other.m_Data, m_Size);
			}
			else
			{
				m_Size = other.m_Size;
				m_Data = other.m_Data;
				m_Cursor = other.m_Cursor;
				m_End = other.m_End;
				m_OwnsMemory = false;
			}
		}
		return *this;
	}

	MemoryStream::MemoryStream(MemoryStream&& other) noexcept
		:IStream(READ | WRITE)
		,m_Data(std::exchange(other.m_Data, nullptr))
		,m_Cursor(std::exchange(other.m_Cursor, nullptr))
		,m_End(std::exchange(other.m_End, nullptr))
		,m_OwnsMemory(std::exchange(other.m_OwnsMemory, false))
	{
		m_Size = std::exchange(other.m_Size, 0);
		m_Name = std::move(other.m_Name);
		m_Access = std::exchange(other.m_Access, 0);
	}

	MemoryStream& MemoryStream::operator=(MemoryStream&& other)noexcept
	{
		if (this != &other)
		{
			if (m_Data && m_OwnsMemory)
				Dealloc(m_Data);

			m_Name = std::move(other.m_Name);
			m_Size = std::exchange(other.m_Size, 0);
			m_Access = std::exchange(other.m_Access, 0);
			m_Data = std::exchange(other.m_Data, nullptr);
			m_Cursor = std::exchange(other.m_Cursor, nullptr);
			m_End = std::exchange(other.m_End, nullptr);
			m_OwnsMemory = std::exchange(other.m_OwnsMemory, false);
		}
		return *this;
	}

	MemoryStream::~MemoryStream()
	{
		Close();
	}

	ssizet MemoryStream::Read(void* buf, ssizet count) const
	{
		if ((m_Cursor + count) > m_End)
			count = m_End - m_Cursor;

		if (count <= 0)
			return 0;

		memcpy(buf, m_Cursor, count);
		m_Cursor += count;

		return count;
	}

	ssizet MemoryStream::Write(const void* buf, ssizet count)
	{
		if (!IsWritable() || count <= 0)
			return 0;

		const auto currentSize = (m_Cursor - m_Data);
		const auto newSize = currentSize + count;
		if (newSize > m_Size)
		{
			if (m_OwnsMemory)
				Realloc(newSize);
			else
				count = m_Size - currentSize;
		}

		if (count <= 0)
			return 0;

		memcpy(m_Cursor, buf, count);
		m_Cursor += count;
		m_End = Max(m_Cursor, m_End);
		return count;
	}

	void MemoryStream::Skip(const ssizet count)
	{
		VerifyLessEqual(m_Cursor + count, m_End, "Trying to skip a MemoryStream outside of its bounds.");
		m_Cursor = Min(m_Cursor + count, m_End);
	}

	void MemoryStream::Seek(const ssizet pos)
	{
		VerifyLessEqual(m_Data + pos, m_End, "Trying to seek a MemoryStream outside of its bounds.");
		m_Cursor = Min(m_Data + pos, m_End);
	}

	SPtr<IStream> MemoryStream::Clone(const bool copyData)const
	{
		if (!copyData)
			return std::make_shared<MemoryStream>(m_Data, m_Size);
		return std::make_shared<MemoryStream>(*this);
	}

	void MemoryStream::Close()
	{
		if (m_Data != nullptr)
		{
			if (m_OwnsMemory)
				Dealloc(m_Data);
			m_Data = nullptr;
		}
	}

	uint8* MemoryStream::DisownMemory()
	{
		m_OwnsMemory = false;
		return m_Data;
	}
}