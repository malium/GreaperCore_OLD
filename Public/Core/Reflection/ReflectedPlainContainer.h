/***********************************************************************************
*   Copyright 2021 Marcos Sánchez Torrent.                                         *
*   All Rights Reserved.                                                           *
***********************************************************************************/

#pragma once

#ifndef CORE_REFLECTION_REFLECTED_PLAIN_CONTAINER_H
#define CORE_REFLECTION_REFLECTED_PLAIN_CONTAINER_H 1

#include "../CorePrerequisites.h"
#include "ReflectedPlainType.h"
#include <array>

namespace greaper
{
	template<>
	struct ReflectedPlainType<String>
	{
		enum { ID = RTI_String }; enum { HasDynamicSize = 1 };

		static ReflectedSize_t ToStream(const String& data, IStream& stream)
		{
			return ReflectedWriteWithSizeHeader(stream, data, [&data, &stream]()
				{
					ReflectedSize_t size = data.size() * sizeof(String::value_type);
					stream.WriteBytes((const uint8*)data.data(), size);
					return size;
				});
		}

		static ReflectedSize_t FromStream(String& data, IStream& stream)
		{
			ReflectedSize_t size = 0;

			ReflectedReadSizeHeader(stream, size);

			ReflectedSize_t stringSize = size - sizeof(ReflectedSize_t);
			data.clear();
			data.resize(stringSize);
			stream.ReadBytes((uint8*)data.data(), stringSize * sizeof(String::value_type));

			return size;
		}

		static ReflectedSize_t GetSize(const String& data)
		{
			ReflectedSize_t dataSize = data.size() * sizeof(String::value_type);
			ReflectedAddHeaderSize(dataSize); // Size Header

			return dataSize;
		}
	};

	template<>
	struct ReflectedPlainType<WString>
	{
		enum { ID = RTI_WString }; enum { HasDynamicSize = 1 };

		static ReflectedSize_t ToStream(const WString& data, IStream& stream)
		{
			return ReflectedWriteWithSizeHeader(stream, data, [&data, &stream]()
				{
					ReflectedSize_t size = data.size() * sizeof(WString::value_type);
					stream.WriteBytes((const uint8*)data.data(), size);
					return size;
				});
		}

		static ReflectedSize_t FromStream(WString& data, IStream& stream)
		{
			ReflectedSize_t size = 0;

			ReflectedReadSizeHeader(stream, size);

			ReflectedSize_t stringSize = size - sizeof(ReflectedSize_t);
			data.clear();
			data.resize(stringSize);
			stream.ReadBytes((uint8*)data.data(), stringSize * sizeof(WString::value_type));

			return size;
		}

		static ReflectedSize_t GetSize(const WString& data)
		{
			ReflectedSize_t dataSize = data.size() * sizeof(WString::value_type);
			ReflectedAddHeaderSize(dataSize); // Size Header

			return dataSize;
		}
	};

	template<class T, sizet N>
	struct ReflectedPlainType<std::array<T, N>>
	{
		using Container_t = std::array<T, N>;
		enum { ID = RTI_Array }; enum { HasDynamicSize = 1 };

		static ReflectedSize_t ToStream(const Container_t& data, IStream& stream)
		{
			return ReflectedWriteWithSizeHeader(stream, data, [&data, &stream]()
				{
					ReflectedSize_t size = 0;
					//const auto elemNum = (ReflectedSize_t)data.size();
					//size += ReflectedWrite(elemNum, stream);

					for (const auto& elem : data)
					{
						size += ReflectedWrite(elem, stream);
					}
					return size;
				});
		}

		static ReflectedSize_t FromStream(Container_t& data, IStream& stream)
		{
			ReflectedSize_t size = 0;

			ReflectedReadSizeHeader(stream, size);

			//ReflectedSize_t elemNum;
			//ReflectedRead(elemNum, stream);
			
			//VerifyEqual(elemNum, N, "Deserializing an array with different size than it should have");

			for (auto& elem : data)
			{
				ReflectedRead(elem, stream);
			}

			return size;
		}

		static ReflectedSize_t GetSize(const Container_t& data)
		{
			ReflectedSize_t dataSize = sizeof(ReflectedSize_t); // ElemNum

			for (const auto& elem : data)
			{
				dataSize += ReflectedSize(elem);
			}

			ReflectedAddHeaderSize(dataSize); // Size Header

			return dataSize;
		}
	};


	template<class T, typename A>
	struct ReflectedPlainType<std::vector<T, A>>
	{
		using Container_t = std::vector<T, A>;
		enum { ID = RTI_Vector }; enum { HasDynamicSize = 1 };

		static ReflectedSize_t ToStream(const Container_t& data, IStream& stream)
		{
			return ReflectedWriteWithSizeHeader(stream, data, [&data, &stream]()
				{
					ReflectedSize_t size = 0;
					const auto elemNum = (ReflectedSize_t)data.size();
					size += ReflectedWrite(elemNum, stream);

					for (const auto& elem : data)
					{
						size += ReflectedWrite(elem, stream);
					}
					return size;
				});
		}

		static ReflectedSize_t FromStream(Container_t& data, IStream& stream)
		{
			ReflectedSize_t size = 0;

			ReflectedReadSizeHeader(stream, size);

			ReflectedSize_t elemNum;
			ReflectedRead(elemNum, stream);

			data.clear();
			if (data.capacity() < elemNum)
				data.reserve(elemNum); // Pre-allocate all elements
			for (ReflectedSize_t i = 0; i < elemNum; ++i)
			{
				T elem;
				ReflectedRead(elem, stream);

				data.push_back(std::move(elem));
			}

			return size;
		}

		static ReflectedSize_t GetSize(const Container_t& data)
		{
			ReflectedSize_t dataSize = sizeof(ReflectedSize_t); // ElemNum

			for (const auto& elem : data)
			{
				dataSize += ReflectedSize(elem);
			}

			ReflectedAddHeaderSize(dataSize); // Size Header

			return dataSize;
		}
	};

	template<class T, typename A>
	struct ReflectedPlainType<std::list<T, A>>
	{
		using Container_t = std::list<T, A>;
		enum { ID = RTI_List }; enum { HasDynamicSize = 1 };

		static ReflectedSize_t ToStream(const Container_t& data, IStream& stream)
		{
			return ReflectedWriteWithSizeHeader(stream, data, [&data, &stream]()
				{
					ReflectedSize_t size = 0;
					const auto elemNum = (ReflectedSize_t)data.size();
					size += ReflectedWrite(elemNum, stream);

					for (const auto& elem : data)
					{
						size += ReflectedWrite(elem, stream);
					}
					return size;
				});
		}

		static ReflectedSize_t FromStream(Container_t& data, IStream& stream)
		{
			ReflectedSize_t size = 0;

			ReflectedReadSizeHeader(stream, size);

			ReflectedSize_t elemNum;
			ReflectedRead(elemNum, stream);

			data.clear();

			for (ReflectedSize_t i = 0; i < elemNum; ++i)
			{
				T elem;
				ReflectedRead(elem, stream);

				data.push_back(std::move(elem));
			}

			return size;
		}

		static ReflectedSize_t GetSize(const Container_t& data)
		{
			ReflectedSize_t dataSize = sizeof(ReflectedSize_t); // ElemNum

			for (const auto& elem : data)
			{
				dataSize += ReflectedSize(elem);
			}

			ReflectedAddHeaderSize(dataSize); // Size Header

			return dataSize;
		}
	};

	template<class T, typename A>
	struct ReflectedPlainType<std::deque<T, A>>
	{
		using Container_t = std::deque<T, A>;
		enum { ID = RTI_Deque }; enum { HasDynamicSize = 1 };

		static ReflectedSize_t ToStream(const Container_t& data, IStream& stream)
		{
			return ReflectedWriteWithSizeHeader(stream, data, [&data, &stream]()
				{
					ReflectedSize_t size = 0;
					const auto elemNum = (ReflectedSize_t)data.size();
					size += ReflectedWrite(elemNum, stream);

					for (const auto& elem : data)
					{
						size += ReflectedWrite(elem, stream);
					}
					return size;
				});
		}

		static ReflectedSize_t FromStream(Container_t& data, IStream& stream)
		{
			ReflectedSize_t size = 0;

			ReflectedReadSizeHeader(stream, size);

			ReflectedSize_t elemNum;
			ReflectedRead(elemNum, stream);

			data.clear();

			for (ReflectedSize_t i = 0; i < elemNum; ++i)
			{
				T elem;
				ReflectedRead(elem, stream);

				data.push_back(std::move(elem));
			}

			return size;
		}

		static ReflectedSize_t GetSize(const Container_t& data)
		{
			ReflectedSize_t dataSize = sizeof(ReflectedSize_t); // ElemNum

			for (const auto& elem : data)
			{
				dataSize += ReflectedSize(elem);
			}

			ReflectedAddHeaderSize(dataSize); // Size Header

			return dataSize;
		}
	};

	template<class T, class C, typename A>
	struct ReflectedPlainType<std::set<T, C, A>>
	{
		using Container_t = std::set<T, C, A>;
		enum { ID = RTI_Set }; enum { HasDynamicSize = 1 };

		static ReflectedSize_t ToStream(const Container_t& data, IStream& stream)
		{
			return ReflectedWriteWithSizeHeader(stream, data, [&data, &stream]()
				{
					ReflectedSize_t size = 0;
					const auto elemNum = (ReflectedSize_t)data.size();
					size += ReflectedWrite(elemNum, stream);

					for (const auto& elem : data)
					{
						size += ReflectedWrite(elem, stream);
					}
					return size;
				});
		}

		static ReflectedSize_t FromStream(Container_t& data, IStream& stream)
		{
			ReflectedSize_t size = 0;

			ReflectedReadSizeHeader(stream, size);

			ReflectedSize_t elemNum;
			ReflectedRead(elemNum, stream);

			data.clear();

			for (ReflectedSize_t i = 0; i < elemNum; ++i)
			{
				T elem;
				ReflectedRead(elem, stream);

				data.emplace(std::move(elem));
			}

			return size;
		}

		static ReflectedSize_t GetSize(const Container_t& data)
		{
			ReflectedSize_t dataSize = sizeof(ReflectedSize_t); // ElemNum

			for (const auto& elem : data)
			{
				dataSize += ReflectedSize(elem);
			}

			ReflectedAddHeaderSize(dataSize); // Size Header

			return dataSize;
		}
	};

	template<class T, class C, typename A>
	struct ReflectedPlainType<std::multiset<T, C, A>>
	{
		using Container_t = std::multiset<T, C, A>;
		enum { ID = RTI_MultiSet }; enum { HasDynamicSize = 1 };

		static ReflectedSize_t ToStream(const Container_t& data, IStream& stream)
		{
			return ReflectedWriteWithSizeHeader(stream, data, [&data, &stream]()
				{
					ReflectedSize_t size = 0;
					const auto elemNum = (ReflectedSize_t)data.size();
					size += ReflectedWrite(elemNum, stream);

					for (const auto& elem : data)
					{
						size += ReflectedWrite(elem, stream);
					}
					return size;
				});
		}

		static ReflectedSize_t FromStream(Container_t& data, IStream& stream)
		{
			ReflectedSize_t size = 0;

			ReflectedReadSizeHeader(stream, size);

			ReflectedSize_t elemNum;
			ReflectedRead(elemNum, stream);

			data.clear();

			for (ReflectedSize_t i = 0; i < elemNum; ++i)
			{
				T elem;
				ReflectedRead(elem, stream);

				data.emplace(std::move(elem));
			}

			return size;
		}

		static ReflectedSize_t GetSize(const Container_t& data)
		{
			ReflectedSize_t dataSize = sizeof(ReflectedSize_t); // ElemNum

			for (const auto& elem : data)
			{
				dataSize += ReflectedSize(elem);
			}

			ReflectedAddHeaderSize(dataSize); // Size Header

			return dataSize;
		}
	};

	template<class T, class H, class C, typename A>
	struct ReflectedPlainType<std::unordered_set<T, H, C, A>>
	{
		using Container_t = std::unordered_set<T, H, C, A>;
		enum { ID = RTI_UnorderedSet }; enum { HasDynamicSize = 1 };

		static ReflectedSize_t ToStream(const Container_t& data, IStream& stream)
		{
			return ReflectedWriteWithSizeHeader(stream, data, [&data, &stream]()
				{
					ReflectedSize_t size = 0;
					const auto elemNum = (ReflectedSize_t)data.size();
					size += ReflectedWrite(elemNum, stream);

					for (const auto& elem : data)
					{
						size += ReflectedWrite(elem, stream);
					}
					return size;
				});
		}

		static ReflectedSize_t FromStream(Container_t& data, IStream& stream)
		{
			ReflectedSize_t size = 0;

			ReflectedReadSizeHeader(stream, size);

			ReflectedSize_t elemNum;
			ReflectedRead(elemNum, stream);

			data.clear();

			for (ReflectedSize_t i = 0; i < elemNum; ++i)
			{
				T elem;
				ReflectedRead(elem, stream);

				data.emplace(std::move(elem));
			}

			return size;
		}

		static ReflectedSize_t GetSize(const Container_t& data)
		{
			ReflectedSize_t dataSize = sizeof(ReflectedSize_t); // ElemNum

			for (const auto& elem : data)
			{
				dataSize += ReflectedSize(elem);
			}

			ReflectedAddHeaderSize(dataSize); // Size Header

			return dataSize;
		}
	};

	template<class T, class H, class C, typename A>
	struct ReflectedPlainType<std::unordered_multiset<T, H, C, A>>
	{
		using Container_t = std::unordered_multiset<T, H, C, A>;
		enum { ID = RTI_UnorderedMultiSet }; enum { HasDynamicSize = 1 };

		static ReflectedSize_t ToStream(const Container_t& data, IStream& stream)
		{
			return ReflectedWriteWithSizeHeader(stream, data, [&data, &stream]()
				{
					ReflectedSize_t size = 0;
					const auto elemNum = (ReflectedSize_t)data.size();
					size += ReflectedWrite(elemNum, stream);

					for (const auto& elem : data)
					{
						size += ReflectedWrite(elem, stream);
					}
					return size;
				});
		}

		static ReflectedSize_t FromStream(Container_t& data, IStream& stream)
		{
			ReflectedSize_t size = 0;

			ReflectedReadSizeHeader(stream, size);

			ReflectedSize_t elemNum;
			ReflectedRead(elemNum, stream);

			data.clear();

			for (ReflectedSize_t i = 0; i < elemNum; ++i)
			{
				T elem;
				ReflectedRead(elem, stream);

				data.emplace(std::move(elem));
			}

			return size;
		}

		static ReflectedSize_t GetSize(const Container_t& data)
		{
			ReflectedSize_t dataSize = sizeof(ReflectedSize_t); // ElemNum

			for (const auto& elem : data)
			{
				dataSize += ReflectedSize(elem);
			}

			ReflectedAddHeaderSize(dataSize); // Size Header

			return dataSize;
		}
	};

	template<class K, class V, class P, typename A>
	struct ReflectedPlainType<std::map<K, V, P, A>>
	{
		using Container_t = std::map<K, V, P, A>;
		enum { ID = RTI_Map }; enum { HasDynamicSize = 1 };

		static ReflectedSize_t ToStream(const Container_t& data, IStream& stream)
		{
			return ReflectedWriteWithSizeHeader(stream, data, [&data, &stream]()
				{
					ReflectedSize_t size = 0;
					const auto elemNum = (ReflectedSize_t)data.size();
					size += ReflectedWrite(elemNum, stream);

					for (const auto& elem : data)
					{
						size += ReflectedWrite(elem.first, stream);
						size += ReflectedWrite(elem.second, stream);
					}
					return size;
				});
		}

		static ReflectedSize_t FromStream(Container_t& data, IStream& stream)
		{
			ReflectedSize_t size = 0;

			ReflectedReadSizeHeader(stream, size);

			ReflectedSize_t elemNum;
			ReflectedRead(elemNum, stream);

			data.clear();

			for (ReflectedSize_t i = 0; i < elemNum; ++i)
			{
				K key;
				ReflectedRead(key, stream);

				V value;
				ReflectedRead(value, stream);

				data.insert_or_assign(key, value);
			}

			return size;
		}

		static ReflectedSize_t GetSize(const Container_t& data)
		{
			ReflectedSize_t dataSize = sizeof(ReflectedSize_t); // ElemNum

			for (const auto& elem : data)
			{
				dataSize += ReflectedSize(elem.first);
				dataSize += ReflectedSize(elem.second);
			}

			ReflectedAddHeaderSize(dataSize); // Size Header

			return dataSize;
		}
	};

	template<class K, class V, class P, typename A>
	struct ReflectedPlainType<std::multimap<K, V, P, A>>
	{
		using Container_t = std::multimap<K, V, P, A>;
		enum { ID = RTI_MultiMap }; enum { HasDynamicSize = 1 };

		static ReflectedSize_t ToStream(const Container_t& data, IStream& stream)
		{
			return ReflectedWriteWithSizeHeader(stream, data, [&data, &stream]()
				{
					ReflectedSize_t size = 0;
					const auto elemNum = (ReflectedSize_t)data.size();
					size += ReflectedWrite(elemNum, stream);

					for (const auto& elem : data)
					{
						size += ReflectedWrite(elem.first, stream);
						size += ReflectedWrite(elem.second, stream);
					}
					return size;
				});
		}

		static ReflectedSize_t FromStream(Container_t& data, IStream& stream)
		{
			ReflectedSize_t size = 0;

			ReflectedReadSizeHeader(stream, size);

			ReflectedSize_t elemNum;
			ReflectedRead(elemNum, stream);

			data.clear();

			for (ReflectedSize_t i = 0; i < elemNum; ++i)
			{
				K key;
				ReflectedRead(key, stream);

				V value;
				ReflectedRead(value, stream);

				data.insert_or_assign(key, value);
			}

			return size;
		}

		static ReflectedSize_t GetSize(const Container_t& data)
		{
			ReflectedSize_t dataSize = sizeof(ReflectedSize_t); // ElemNum

			for (const auto& elem : data)
			{
				dataSize += ReflectedSize(elem.first);
				dataSize += ReflectedSize(elem.second);
			}

			ReflectedAddHeaderSize(dataSize); // Size Header

			return dataSize;
		}
	};

	template<class K, class V, class P, typename A>
	struct ReflectedPlainType<std::unordered_map<K, V, P, A>>
	{
		using Container_t = std::unordered_map<K, V, P, A>;
		enum { ID = RTI_UnorderedMap }; enum { HasDynamicSize = 1 };

		static ReflectedSize_t ToStream(const Container_t& data, IStream& stream)
		{
			return ReflectedWriteWithSizeHeader(stream, data, [&data, &stream]()
				{
					ReflectedSize_t size = 0;
					const auto elemNum = (ReflectedSize_t)data.size();
					size += ReflectedWrite(elemNum, stream);

					for (const auto& elem : data)
					{
						size += ReflectedWrite(elem.first, stream);
						size += ReflectedWrite(elem.second, stream);
					}
					return size;
				});
		}

		static ReflectedSize_t FromStream(Container_t& data, IStream& stream)
		{
			ReflectedSize_t size = 0;

			ReflectedReadSizeHeader(stream, size);

			ReflectedSize_t elemNum;
			ReflectedRead(elemNum, stream);

			data.clear();

			for (ReflectedSize_t i = 0; i < elemNum; ++i)
			{
				K key;
				ReflectedRead(key, stream);

				V value;
				ReflectedRead(value, stream);

				data.insert_or_assign(key, value);
			}

			return size;
		}

		static ReflectedSize_t GetSize(const Container_t& data)
		{
			ReflectedSize_t dataSize = sizeof(ReflectedSize_t); // ElemNum

			for (const auto& elem : data)
			{
				dataSize += ReflectedSize(elem.first);
				dataSize += ReflectedSize(elem.second);
			}

			ReflectedAddHeaderSize(dataSize); // Size Header

			return dataSize;
		}
	};

	template<class K, class V, class P, typename A>
	struct ReflectedPlainType<std::unordered_multimap<K, V, P, A>>
	{
		using Container_t = std::multimap<K, V, P, A>;
		enum { ID = RTI_UnorderedMultiMap }; enum { HasDynamicSize = 1 };

		static ReflectedSize_t ToStream(const Container_t& data, IStream& stream)
		{
			return ReflectedWriteWithSizeHeader(stream, data, [&data, &stream]()
				{
					ReflectedSize_t size = 0;
					const auto elemNum = (ReflectedSize_t)data.size();
					size += ReflectedWrite(elemNum, stream);

					for (const auto& elem : data)
					{
						size += ReflectedWrite(elem.first, stream);
						size += ReflectedWrite(elem.second, stream);
					}
					return size;
				});
		}

		static ReflectedSize_t FromStream(Container_t& data, IStream& stream)
		{
			ReflectedSize_t size = 0;

			ReflectedReadSizeHeader(stream, size);

			ReflectedSize_t elemNum;
			ReflectedRead(elemNum, stream);

			data.clear();

			for (ReflectedSize_t i = 0; i < elemNum; ++i)
			{
				K key;
				ReflectedRead(key, stream);

				V value;
				ReflectedRead(value, stream);

				data.insert_or_assign(key, value);
			}

			return size;
		}

		static ReflectedSize_t GetSize(const Container_t& data)
		{
			ReflectedSize_t dataSize = sizeof(ReflectedSize_t); // ElemNum

			for (const auto& elem : data)
			{
				dataSize += ReflectedSize(elem.first);
				dataSize += ReflectedSize(elem.second);
			}

			ReflectedAddHeaderSize(dataSize); // Size Header

			return dataSize;
		}
	};
}

#endif /* CORE_REFLECTION_REFLECTED_PLAIN_CONTAINER_H */
