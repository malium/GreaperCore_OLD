/***********************************************************************************
*   Copyright 2021 Marcos S�nchez Torrent.                                         *
*   All Rights Reserved.                                                           *
***********************************************************************************/

#pragma once

#ifndef CORE_EVENT_H
#define CORE_EVENT_H 1

#include "Memory.h"
#include <functional>

namespace greaper
{
	template<class... Args>
	class Event;

	template<class... Args>
	class EventHandler
	{
		Event<Args...>* m_Event = nullptr;
		uint32 m_ID = 0;
	public:
		INLINE ~EventHandler()
		{
			if (m_Event != nullptr)
			{
				m_Event->Disconnect(this);
			}
		}
		friend class Event<Args...>;
	};

	template<class... Args>
	struct EventHandlerID
	{
		using HandlerFunction = std::function<void(Args...)>;
		HandlerFunction Function;
		uint32 ID;
	};

	template<>
	struct EventHandlerID<void>
	{
		using HandlerFunction = std::function<void()>;
		HandlerFunction Function;
		uint32 ID;
	};

	template<class... Args>
	class Event
	{
		Vector<EventHandlerID<Args...>> m_Handlers;
		String m_Name;
		uint32 m_LastID;

	public:
		using HandlerType = EventHandler<Args...>;
		using HandlerFunction = typename EventHandlerID<Args...>::HandlerFunction;
		
		Event(String eventName = "unnamed") noexcept
			:m_Name(std::move(eventName))
			,m_LastID(0)
		{

		}
		~Event() = default;
		Event(const Event&) = delete;
		Event& operator=(const Event&) = delete;

		const String& GetName()const noexcept
		{
			return m_Name;
		}

		void Connect(HandlerType& handler, HandlerFunction function) noexcept
		{
			EventHandlerID<Args...> hnd;
			hnd.Function = std::move(function);
			hnd.ID = m_LastID++;
			handler.m_Event = this;
			handler.m_ID = hnd.ID;
			m_Handlers.push_back(std::move(hnd));
		}

		void Disconnect(HandlerType& handler) noexcept
		{
			for (auto it = m_Handlers.begin(); it != m_Handlers.end(); ++it)
			{
				EventHandlerID<Args...>& hnd = *it;
				if (hnd.ID == handler.m_ID)
				{
					handler.m_Event = nullptr;
					m_Handlers.erase(it);
					break;
				}
			}
		}

		void Trigger(Args&&... args) noexcept
		{
			for (EventHandlerID<Args...>& hnd : m_Handlers)
			{
				hnd.Function(std::forward<Args>(args)...);
			}
		}
	};
}

#endif /* CORE_EVENT_H */
