/***********************************************************************************
*   Copyright 2021 Marcos Sánchez Torrent.                                         *
*   All Rights Reserved.                                                           *
***********************************************************************************/

//#include "../Stream.h"

namespace greaper
{
	template<typename T>
	INLINE IStream& IStream::operator>>(T& val)
	{
		Read((void*)&val, sizeof(val));
		return *this;
	}

	IStream::IStream(const uint16 accessMode)
		:m_Access(accessMode)
	{

	}

	IStream::IStream(StringView name, const uint16 accessMode)
		:m_Name(name)
		,m_Access(accessMode)
	{

	}

	void IStream::Align(uint32 count)
	{
		if (count <= 1)
			return;

		const auto alignOffset = (count - (Tell() & (count - 1))) & (count - 1);
		Skip(alignOffset);
	}
}