/***********************************************************************************
*   Copyright 2021 Marcos S�nchez Torrent.                                         *
*   All Rights Reserved.                                                           *
***********************************************************************************/

#pragma once

#ifndef CORE_MEMORY_STREAM_H
#define CORE_MEMORY_STREAM_H 1

#include "Stream.h"

namespace greaper
{
	class MemoryStream : public IStream
	{
	protected:
		uint8* m_Data;
		mutable uint8* m_Cursor;
		uint8* m_End;
		bool m_OwnsMemory;

		void Realloc(sizet bytes);

	public:
		MemoryStream();

		MemoryStream(sizet capacity);

		MemoryStream(void* memory, sizet size);

		MemoryStream(const MemoryStream& other);
		MemoryStream& operator=(const MemoryStream& other);
		MemoryStream(MemoryStream&& other) noexcept;
		MemoryStream& operator=(MemoryStream&& other) noexcept;

		~MemoryStream();

		INLINE bool IsFile()const noexcept override { return false; }

		uint8* GetData()const;

		uint8* GetCursor()const;

		ssizet Read(void* buf, ssizet count)const override;

		ssizet Write(const void* buf, ssizet count) override;

		void Skip(ssizet count) override;

		void Seek(ssizet pos) override;

		ssizet Tell()const override;

		bool Eof()const override;

		SPtr<IStream> Clone(bool copyData = true)const override;

		void Close() override;

		uint8* DisownMemory();
	};
}

#endif /* CORE_MEMORY_STREAM_H */