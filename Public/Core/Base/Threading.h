/***********************************************************************************
*   Copyright 2021 Marcos S�nchez Torrent.                                         *
*   All Rights Reserved.                                                           *
***********************************************************************************/

#pragma once

#ifndef CORE_THREADING_H
#define CORE_THREADING_H 1

#include "../Memory.h"

#if PLT_WINDOWS
#include "Win/WinThreading.h"
#elif PLT_LINUX
#incude "Lnx/LnxThreading.h"
#endif
#include <mutex>
#include <condition_variable>

namespace greaper
{
	class Mutex
	{
		MutexHandle m_Handle;
	public:
		Mutex() noexcept
		{
			Impl::MutexImpl::Initialize(m_Handle);
		}

		Mutex(const Mutex&) = delete;
		Mutex& operator=(const Mutex&) = delete;
		Mutex(Mutex&& other) noexcept
		{
			DuplicateMemory(other.m_Handle, m_Handle);
			Impl::MutexImpl::Invalidate(other.m_Handle);
		}
		Mutex& operator=(Mutex&& other)noexcept
		{
			if(this != &other)
			{
				if(Impl::MutexImpl::IsValid(m_Handle))
					Impl::MutexImpl::Deinitialize(m_Handle);
				DuplicateMemory(other.m_Handle, m_Handle);
				Impl::MutexImpl::Invalidate(other.m_Handle);
			}
			return *this;
		}
		~Mutex()
		{
			if(Impl::MutexImpl::IsValid(m_Handle))
				Impl::MutexImpl::Deinitialize(m_Handle);
		}

		void lock() noexcept
		{
			Verify(Impl::MutexImpl::IsValid(m_Handle), "Trying to lock an invalid mutex.");
			Impl::MutexImpl::Lock(m_Handle);
		}

		bool try_lock() noexcept
		{
			if(!Impl::MutexImpl::IsValid(m_Handle))
				return false;
			return Impl::MutexImpl::TryLock(m_Handle);
		}

		void unlock() noexcept
		{
			Verify(Impl::MutexImpl::IsValid(m_Handle), "Trying to unlock an invalid mutex.");
			return Impl::MutexImpl::Unlock(m_Handle);
		}

		[[nodiscard]] const MutexHandle* GetHandle()const noexcept
		{
			return &m_Handle;
		}
		[[nodiscard]] MutexHandle* GetHandle() noexcept
		{
			return &m_Handle;
		}
	};

	class RecursiveMutex
	{
		RecursiveMutexHandle m_Handle;

	public:
		RecursiveMutex() noexcept
		{
			Impl::RecursiveMutexImpl::Initialize(m_Handle);
		}
		RecursiveMutex(const RecursiveMutex&) = delete;
		RecursiveMutex& operator=(const RecursiveMutex&) = delete;
		RecursiveMutex(RecursiveMutex&& other) noexcept
		{
			DuplicateMemory(other.m_Handle, m_Handle);
			Impl::RecursiveMutexImpl::Invalidate(other.m_Handle);
		}
		RecursiveMutex& operator=(RecursiveMutex&& other) noexcept
		{
			if(this != &other)
			{
				if(Impl::RecursiveMutexImpl::IsValid(m_Handle))
					Impl::RecursiveMutexImpl::Deinitialize(m_Handle);
				DuplicateMemory(other.m_Handle, m_Handle);
				Impl::RecursiveMutexImpl::Invalidate(other.m_Handle);
			}
			return *this;
		}
		~RecursiveMutex()
		{
			if(Impl::RecursiveMutexImpl::IsValid(m_Handle))
				Impl::RecursiveMutexImpl::Deinitialize(m_Handle);
		}

		void lock() noexcept
		{
			Verify(Impl::RecursiveMutexImpl::IsValid(m_Handle), "Trying to lock an invalid recursive mutex");
			Impl::RecursiveMutexImpl::Lock(m_Handle);
		}

		bool try_lock() noexcept
		{
			if(!Impl::RecursiveMutexImpl::IsValid(m_Handle))
				return false;
			return Impl::RecursiveMutexImpl::TryLock(m_Handle);
		}

		void unlock() noexcept
		{
			Verify(Impl::RecursiveMutexImpl::IsValid(m_Handle), "Trying to unlock an invalid recursive mutex");
			Impl::RecursiveMutexImpl::Unlock(m_Handle);
		}

		[[nodiscard]] const RecursiveMutexHandle* GetHandle()const noexcept
		{
			return &m_Handle;
		}

		[[nodiscard]] RecursiveMutexHandle* GetHandle() noexcept
		{
			return &m_Handle;
		}
	};

	class RWMutex
	{
		RWMutexHandle m_Handle;

	public:
		RWMutex() noexcept
		{
			Impl::RWMutexImpl::Initialize(m_Handle);
		}
		RWMutex(const RWMutex&) = delete;
		RWMutex& operator=(const RWMutex&) = delete;
		RWMutex(RWMutex&& other) noexcept
		{
			DuplicateMemory(other.m_Handle, m_Handle);
			Impl::RWMutexImpl::Invalidate(other.m_Handle);
		}
		RWMutex& operator=(RWMutex&& other) noexcept
		{
			if(this != &other)
			{
				if(Impl::RWMutexImpl::IsValid(m_Handle))
					Impl::RWMutexImpl::Deinitialize(m_Handle);
				DuplicateMemory(other.m_Handle, m_Handle);
				Impl::RWMutexImpl::Invalidate(other.m_Handle);
			}
			return *this;
		}
		~RWMutex()
		{
			if(Impl::RWMutexImpl::IsValid(m_Handle))
				Impl::RWMutexImpl::Deinitialize(m_Handle);
		}

		void lock() noexcept
		{
			Verify(Impl::RWMutexImpl::IsValid(m_Handle), "Trying to lock an invalid read-write mutex");
			Impl::RWMutexImpl::Lock(m_Handle);
		}

		void lock_shared() noexcept
		{
			Verify(Impl::RWMutexImpl::IsValid(m_Handle), "Trying to lock shared an invalid read-write mutex");
			Impl::RWMutexImpl::LockShared(m_Handle);
		}

		void unlock() noexcept
		{
			Verify(Impl::RWMutexImpl::IsValid(m_Handle), "Trying to unlock an invalid read-write mutex");
			Impl::RWMutexImpl::Unlock(m_Handle);
		}

		void unlock_shared() noexcept
		{
			Verify(Impl::RWMutexImpl::IsValid(m_Handle), "Trying to unlock shared an invalid read-write mutex");
			Impl::RWMutexImpl::UnlockShared(m_Handle);
		}

		bool try_lock() noexcept
		{
			if(!Impl::RWMutexImpl::IsValid(m_Handle))
				return false;
			return Impl::RWMutexImpl::TryLock(m_Handle);
		}

		bool try_lock_shared() noexcept
		{
			if(!Impl::RWMutexImpl::IsValid(m_Handle))
				return false;
			return Impl::RWMutexImpl::TryLockShared(m_Handle);
		}

		[[nodiscard]] const RWMutexHandle* GetHandle()const noexcept
		{
			return &m_Handle;
		}

		[[nodiscard]] RWMutexHandle* GetHandle() noexcept
		{
			return &m_Handle;
		}
	};

	class SpinLock
	{
		static constexpr uint32 SpinCount = 4000;
		std::atomic_flag m_Lock;

	public:
		SpinLock() noexcept = default;
		SpinLock(const SpinLock&) = delete;
		SpinLock& operator=(const SpinLock&) = delete;
		~SpinLock() = default;

		INLINE void lock() noexcept
		{
			while(true)
			{
				for(uint32 i = 0; i < SpinCount; ++i)
				{
					if(try_lock())
						return;
				}
				THREAD_YIELD();
			}
		}

		INLINE bool try_lock() noexcept
		{
			const auto res = !m_Lock.test_and_set(std::memory_order::memory_order_acquire);
			return res;
		}

		INLINE void unlock() noexcept
		{
			m_Lock.clear(std::memory_order_release);
		}
	};

	template<class Mtx>
	using Lock = std::lock_guard<Mtx>;

	template<class Mtx>
	using UniqueLock = std::unique_lock<Mtx>;

	class SharedLock
	{
		RWMutex& m_Mutex;

	public:
		using mutex_type = RWMutex;

		explicit SharedLock(RWMutex& mutex) noexcept
			:m_Mutex(mutex)
		{
			m_Mutex.lock_shared();
		}

		SharedLock(RWMutex& mutex, std::adopt_lock_t) noexcept
			:m_Mutex(mutex)
		{

		}

		SharedLock(const SharedLock&) = delete;
		SharedLock& operator=(const SharedLock&) = delete;

		RWMutex* mutex() noexcept
		{
			return &m_Mutex;
		}

		~SharedLock()
		{
			m_Mutex.unlock_shared();
		}
	};

	class Signal
	{
		SignalHandle m_Handle;

		void Wait(const UniqueLock<Mutex>& lock) noexcept
		{
			Impl::SignalImpl::Wait(m_Handle, *lock.mutex()->GetHandle());
		}
		void Wait(const UniqueLock<RWMutex>& lock) noexcept
		{
			Impl::SignalImpl::WaitRW(m_Handle, *lock.mutex()->GetHandle());
		}
		void Wait(const UniqueLock<RecursiveMutex>& lock) noexcept
		{
			Impl::SignalImpl::WaitRecursive(m_Handle, *lock.mutex()->GetHandle());
		}
		void WaitShared(const UniqueLock<RWMutex>& lock) noexcept
		{
			Impl::SignalImpl::WaitShared(m_Handle, *lock.mutex()->GetHandle());
		}
		bool WaitFor(const UniqueLock<Mutex>& lock, const uint32 millis) noexcept
		{
			Impl::SignalImpl::WaitFor(m_Handle, *lock.mutex()->GetHandle(), millis);
		}
		bool WaitFor(const UniqueLock<RWMutex>& lock, const uint32 millis) noexcept
		{
			Impl::SignalImpl::WaitForRW(m_Handle, *lock.mutex()->GetHandle(), millis);
		}
		bool WaitFor(const UniqueLock<RecursiveMutex>& lock, const uint32 millis) noexcept
		{
			Impl::SignalImpl::WaitForRecursive(m_Handle, *lock.mutex()->GetHandle(), millis);
		}
		bool WaitForShared(const UniqueLock<RWMutex>& lock, const uint32 millis) noexcept
		{
			Impl::SignalImpl::WaitForShared(m_Handle, *lock.mutex()->GetHandle(), millis);
		}

	public:
		Signal() noexcept
		{
			Impl::SignalImpl::Initialize(m_Handle);
		}
		Signal(const Signal&) = delete;
		Signal& operator=(const Signal&) = delete;
		Signal(Signal&& other) noexcept
		{
			DuplicateMemory(other.m_Handle, m_Handle);
			Impl::SignalImpl::Invalidate(other.m_Handle);
		}
		Signal& operator=(Signal&& other)noexcept
		{
			if(this != &other)
			{
				if(Impl::SignalImpl::IsValid(m_Handle))
					Impl::SignalImpl::Deinitialize(m_Handle);
				DuplicateMemory(other.m_Handle, m_Handle);
				Impl::SignalImpl::Invalidate(other.m_Handle);
			}
			return *this;
		}
		~Signal()
		{
			if(Impl::SignalImpl::IsValid(m_Handle))
				Impl::SignalImpl::Deinitialize(m_Handle);
		}

		void notify_one() noexcept
		{
			Verify(Impl::SignalImpl::IsValid(m_Handle), "Trying to use an invalid SignalHandle.");
			Impl::SignalImpl::NotifyOne(m_Handle);
		}

		void notify_all() noexcept
		{
			Verify(Impl::SignalImpl::IsValid(m_Handle), "Trying to use an invalid SignalHandle.");
			Impl::SignalImpl::NotifyAll(m_Handle);
		}

		template<class Mtx>
		void wait(const UniqueLock<Mtx>& lock) noexcept
		{
			Verify(Impl::SignalImpl::IsValid(m_Handle), "Trying to use an invalid SignalHandle.");
			Wait(lock);
		}

		void wait_shared(const UniqueLock<RWMutex>& lock) noexcept
		{
			Verify(Impl::SignalImpl::IsValid(m_Handle), "Trying to use an invalid SignalHandle.");
			WaitShared(lock);
		}

		template<class Mtx, class Pred>
		void wait(const UniqueLock<Mtx>& lock, Pred pred) noexcept
		{
			Verify(Impl::SignalImpl::IsValid(m_Handle), "Trying to use an invalid SignalHandle.");
			while(!pred())
				Wait(lock);
		}

		template<class Pred>
		void wait_shared(const UniqueLock<RWMutex>& lock, Pred pred) noexcept
		{
			Verify(Impl::SignalImpl::IsValid(m_Handle), "Trying to use an invalid SignalHandle.");
			while(!pred())
				WaitShared(lock);
		}

		template<class Mtx, class Rep, class Period>
		bool wait_for(const UniqueLock<Mtx>& lock, const std::chrono::duration<Rep, Period>& relativeTime) noexcept
		{
			Verify(Impl::SignalImpl::IsValid(m_Handle), "Trying to use an invalid SignalHandle.");
			const auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(relativeTime).count();
			return WaitFor(lock, millis);
		}

		template<class Rep, class Period>
		bool wait_for_shared(const UniqueLock<RWMutex>& lock, const std::chrono::duration<Rep, Period>& relativeTime) noexcept
		{
			Verify(Impl::SignalImpl::IsValid(m_Handle), "Trying to use an invalid SignalHandle.");
			const auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(relativeTime).count();
			return WaitForShared(lock, millis);
		}

		template<class Mtx, class Rep, class Period, class Pred>
		bool wait_for(const UniqueLock<Mtx>& lock, const std::chrono::duration<Rep, Period>& relativeTime, Pred pred) noexcept
		{
			Verify(Impl::SignalImpl::IsValid(m_Handle), "Trying to use an invalid SignalHandle.");
			const auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(relativeTime).count();
			while(!pred())
			{
				if(!WaitFor(lock, millis))
				return pred();
			}
			return true;
		}

		template<class Rep, class Period, class Pred>
		bool wait_for_shared(const UniqueLock<RWMutex>& lock, const std::chrono::duration<Rep, Period>& relativeTime, Pred pred) noexcept
		{
			Verify(Impl::SignalImpl::IsValid(m_Handle), "Trying to use an invalid SignalHandle.");
			const auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(relativeTime).count();
			while(!pred())
			{
				if(!WaitForShared(lock, millis))
				return pred();
			}
			return true;
		}

		template<class Mtx, class _Clock, class _Duration>
		bool wait_for(const UniqueLock<Mtx>& lock, const std::chrono::time_point<_Clock, _Duration>& absoluteTime) noexcept
		{
			Verify(Impl::SignalImpl::IsValid(m_Handle), "Trying to use an invalid SignalHandle.");
			const auto relativeTime = absoluteTime - _Clock::now();
			const auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(relativeTime).count();
			return WaitFor(lock, millis);
		}

		template<class _Clock, class _Duration>
		bool wait_for_shared(const UniqueLock<RWMutex>& lock, const std::chrono::time_point<_Clock, _Duration>& absoluteTime) noexcept
		{
			Verify(Impl::SignalImpl::IsValid(m_Handle), "Trying to use an invalid SignalHandle.");
			const auto relativeTime = absoluteTime - _Clock::now();
			const auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(relativeTime).count();
			return WaitForShared(lock, millis);
		}

		template<class Mtx, class _Clock, class _Duration, class Pred>
		bool wait_for(const UniqueLock<Mtx>& lock, const std::chrono::time_point<_Clock, _Duration>& absoluteTime, Pred pred) noexcept
		{
			Verify(Impl::SignalImpl::IsValid(m_Handle), "Trying to use an invalid SignalHandle.");
			const auto relativeTime = absoluteTime - _Clock::now();
			const auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(relativeTime).count();
			while(!pred())
			{
				if(!WaitFor(lock, millis))
					return pred();	
			}
			return true;
		}

		template<class _Clock, class _Duration, class Pred>
		bool wait_for(const UniqueLock<RWMutex>& lock, const std::chrono::time_point<_Clock, _Duration>& absoluteTime, Pred pred) noexcept
		{
			Verify(Impl::SignalImpl::IsValid(m_Handle), "Trying to use an invalid SignalHandle.");
			const auto relativeTime = absoluteTime - _Clock::now();
			const auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(relativeTime).count();
			while(!pred())
			{
				if(!WaitForShared(lock, millis))
					return pred();	
			}
			return true;
		}

		[[nodiscard]] const SignalHandle* GetHandle()const noexcept
		{
			return &m_Handle;
		}

		[[nodiscard]] SignalHandle* GetHandle() noexcept
		{
			return &m_Handle;
		}
	};
}

#endif /* CORE_THREADING_H */