/***********************************************************************************
*   Copyright 2021 Marcos Sánchez Torrent.                                         *
*   All Rights Reserved.                                                           *
***********************************************************************************/

#pragma once

#ifndef GREAPER_CORE_MEMORY_H
#define GREAPER_CORE_MEMORY_H 1

#include "PHAL.h"
#include <type_traits>
#include <vector>
#include <list>
#include <queue>
#include <deque>
#include <stack>
#include <string>
#include <string_view>
#include <set>
#include <unordered_map>
#include <unordered_set>

namespace greaper
{
	template<class T>
	class MemoryAllocator
	{
	public:
		static void* Allocate(sizet byteSize)
		{
			if (bytes == 0)
				return nullptr;

			void* mem = PlatformAlloc(byteSize);
			// TODO
			// Add null checking on debug builds
			return mem;
		}

		static void* AllocateAligned(sizet byteSize, sizet alignment)
		{
			if (bytes == 0)
				return nullptr;
			if (alignment == 0)
				return Allocate(byteSize);

			void* mem = PlatformAlignedAlloc(byteSize, aligment);
			// TODO
			// Add null checking on debug builds
			return mem;
		}

		static void Deallocate(void* mem)
		{
			if (mem == nullptr)
				return; // TODO: Add free after null check on debug builds

			PlatformDealloc(mem);
		}

		static void DeallocateAligned(void* mem)
		{
			if (mem == nullptr)
				return; // TODO: Add free after null check on debug builds

			PlatformAlignedDealloc(mem);
		}
	};

	class GenericAllocator { };

	template<class _Alloc_>
	INLINE void* _Alloc(sizet byteSize)
	{
		return MemoryAllocator<_Alloc_>::Allocate(byteSize);
	}

	template<class _Alloc_, class T>
	INLINE T* _AllocN(sizet count)
	{
		return static_cast<T*>(MemoryAllocator<_Alloc_>::Allocate(sizeof(T) * count));
	}

	template<class _Alloc_, class T, class... Args>
	INLINE T _Construct(sizet count, Args&&... args)
	{
		T* mem = _AllocN<_Alloc_, T>(count);
		for (sizet i = 0; i < count; ++i)
			new (reinterpret_cast<void*>(&mem[i]))T(std::forward<Args>(args)...);
		return mem;
	}

	template<class _Alloc_>
	INLINE void _Dealloc(void* mem)
	{
		MemoryAllocator<_Alloc_>::Deallocate(mem);
	}

	template<class _Alloc_, class T>
	INLINE void _Destruct(T* ptr, sizet count)
	{
		for (sizet i = 0; i < count; ++i)
			ptr[i].~T();
		MemoryAllocator<_Alloc_>::Deallocate(ptr);
	}

#define AllocA(bytes, alloc) _Alloc<alloc>(bytes)
#define Alloc(bytes) _Alloc<GenericAllocator>(bytes)
#define AllocAT(T, alloc) _AllocN<alloc, T>(1)
#define AllocT(T) _AllocN<GenericAllocator, T>(1)
#define AllocATN(T, count, alloc) _AllocN<alloc, T>(count)
#define AllocTN(T, count) _AllocN<GenericAllocator, T>(count)
#define ConstructA(T, alloc, ...) _Construct<alloc, T>(1, __VA_ARGS__)
#define Construct(T, ...) _Construct<GenericAllocator, T>(1, __VA_ARGS__)
#define ConstructAN(T, count, alloc, ...) _Construct<alloc, T>(count, __VA_ARGS__)
#define ConstructN(T, count, ...) _Construct<GenericAllocator, T>(count, __VA_ARGS__)

#define DeallocA(ptr, alloc) _Dealloc<alloc>(ptr)
#define Dealloc(ptr) _Dealloc<GenericAllocator>(ptr)
#define DestroyA(ptr, alloc) _Destroy<alloc>(ptr, 1)
#define Destroy(ptr) _Destroy<GenericAllocator>(ptr, 1)
#define DestroyAN(ptr, count, alloc) _Destroy<alloc>(ptr, count)
#define DestroyN(ptr, count) _Destroy<GenericAllocator>(ptr, count)

#if GREAPER_USE_BASIC_TYPEINFO
	template<class T, sizet::Type N>
#else
	template<class T, sizet N>
#endif
	INLINE constexpr sizet ArraySize(T(&)[N])noexcept { return N; }

	template<class T>
	INLINE void ClearMemory(T& obj, sizet count = 1)noexcept
	{
		memset(&obj, 0, sizeof(T) * count);
	}

#define MemoryFriend()\
template<class _Alloc_, class T, class... Args> friend T* greaper::_Construct(sizet count, Args&&... args);\
template<class _Alloc_, class T> friend void greaper::_Destroy(T* ptr, sizet count)

	template<class T, class _Alloc_ = GenericAllocator>
	class Destructor
	{
		constexpr Destructor() noexcept = default;
		
		template<class T2, std::enable_if_t<std::is_convertible<T2*, T*>::value, int> = 0>
		constexpr Destructor(const Destructor<T2, _Alloc_>& other)
		{
			UNUSED(other);
		}

		void operator()(T* ptr)const
		{
			_DestructATN<_Alloc_, T>(ptr, 1);
		}
	};

	template<class T, class _Alloc_ = GenericAllocator>
	class StdAlloc
	{
	public:
		using value_type = T;
		using pointer = value_type*;
		using const_pointer = const value_type*;
		using reference = value_type&;
		using const_reference = const value_type&;
#if GREAPER_USE_BASIC_TYPEINFO
		using size_type = sizet::Type;
		using difference_type = ptrint::Type;
#else
		using size_type = sizet;
		using difference_type = ptrint;
#endif

		StdAlloc()noexcept = default;
		StdAlloc(StdAlloc&&)noexcept = default;
		StdAlloc(const StdAlloc&)noexcept = default;

		template<class U, class Alloc2> INLINE StdAlloc(const StdAlloc<U, Alloc2>& other) { UNUSED(other); }
		template<class U, class Alloc2> INLINE constexpr bool operator==(const StdAlloc<U, Alloc2>&) const noexcept { return true; }
		template<class U, class Alloc2> INLINE constexpr bool operator!=(const StdAlloc<U, Alloc2>&) const noexcept { return false; }

		template<class U> class rebind { public: using other = StdAlloc<U, _Alloc_>; };

		INLINE T* allocate(const size_t num)
		{
			if (num == 0)
				return nullptr;
			if (num > max_size())
				return nullptr;

			void*const p = _AllocN<_Alloc_, T>(num);
			if (!p)
				return nullptr;
			return static_cast<T*>(p);
		}

		INLINE void deallocate(pointer p, size_type)
		{
			_Dealloc<_Alloc_>(p);
		}

		INLINE constexpr size_t max_size() { return std::numeric_limits<size_type>::max() / sizeof(T); }
		INLINE void destroy(pointer p) { (p)->~T(); }

		template<class... Args>
		INLINE void construct(pointer p, Args&&... args)noexcept { new(p)T(std::forward<Args>(args)...); }
	};

	template<typename T, typename A = StdAlloc<T>>
	using BasicString = std::basic_string<T, std::char_traits<T>, A>;
	template<typename T>
	using BasicStringView = std::basic_string_view<T, std::char_traits<T>>;

	template<typename T, typename A = StdAlloc<T>>
	using BasicStringStream = std::basic_stringstream<T, std::char_traits<T>, A>;

#if GREAPER_USE_BASIC_TYPEINFO
	using String = BasicString<achar::Type>;
	using StringView = BasicStringView<achar::Type>;
	using StringStream = BasicStringStream<achar::Type>;
	using WString = BasicString<wchar::Type>;
	using WStringView = BasicString<wchar::Type>;
	using WStringStream = BasicStringStream<wchar::Type>;
	using U16String = BasicString<u16char::Type>;
	using U16StringStream = BasicStringStream<u16char::Type>;
	using U32String = BasicString<u32char::Type>;
	using U32StringStream = BasicStringStream<u32char::Type>;
#else
	using String = BasicString<achar>;
	using StringView = BasicStringView<achar>;
	using StringStream = BasicStringStream<achar>;
	using WString = BasicString<wchar>;
	using WStringView = BasicString<wchar>;
	using WStringStream = BasicStringStream<wchar>;
	using U16String = BasicString<u16char>;
	using U16StringStream = BasicStringStream<u16char>;
	using U32String = BasicString<u32char>;
	using U32StringStream = BasicStringStream<u32char>;
#endif

	template<typename T, typename A = StdAlloc<T>>
	using Vector = std::vector<T, A>;

	using StringVec = Vector<String>;
	using WStringVec = Vector<WString>;

	template<typename T, typename A = StdAlloc<T>>
	using Queue = std::queue<T, std::deque<T, A>>;

	template<typename T, typename A = StdAlloc<T>>
	using Deque = std::deque<T, A>;

	template<typename T, typename A = StdAlloc<T>>
	using List = std::list<T, A>;

	template<typename T, typename A = StdAlloc<T>>
	using ForwardList = std::forward_list<T, A>;

	template<typename T, typename A = StdAlloc<T>>
	using Stack = std::stack<T, std::deque<T, A>>;

	template<typename K, typename P = std::less<K>, typename A = StdAlloc<K>>
	using Set = std::set<K, P, A>;

	template<typename K, typename V, typename P = std::less<K>, typename A = StdAlloc<std::pair<const K, V>>>
	using Map = std::map<K, V, P, A>;

	template<typename K, typename P = std::less<K>, typename A = StdAlloc<K>>
	using MultiSet = std::multiset<K, P, A>;

	template<typename K, typename V, typename P = std::less<K>, typename A = StdAlloc<std::pair<const K, V>>>
	using MultiMap = std::multimap<K, V, P, A>;

	struct EnumClassHash
	{
		template<typename T>
		INLINE constexpr std::size_t operator()(T t)const
		{
			return static_cast<std::size_t>(t);
		}
	};
	template<typename Key>
	using HashType = typename std::conditional_t<std::is_enum_v<Key>, EnumClassHash, std::hash<Key>>;

	template<typename T, typename H = HashType<T>, typename C = std::equal_to<T>, typename A = StdAlloc<T>>
	using UnorderedSet = std::unordered_set<T, H, C, A>;

	template<typename K, typename V, typename H = HashType<K>, typename C = std::equal_to<K>, typename A = StdAlloc<std::pair<const K, V>>>
	using UnorderedMap = std::unordered_map<K, V, H, C, A>;

	template<typename K, typename V, typename H = HashType<K>, typename C = std::equal_to<K>, typename A = StdAlloc<std::pair<const K, V>>>
	using UnorderedMultiMap = std::unordered_multimap<K, V, H, C, A>;
}

namespace std
{
	template<>
	struct hash<greaper::String>
	{
		INLINE size_t operator()(const greaper::String& str)const noexcept
		{
			return std::_Hash_array_representation(str.data(), str.size());
		}
	};

	template<>
	struct hash<greaper::WString>
	{
		INLINE size_t operator()(const greaper::WString& str)const noexcept
		{
			return std::_Hash_array_representation(str.data(), str.size());
		}
	};
}

#endif /* GREAPER_CORE_MEMORY_H */