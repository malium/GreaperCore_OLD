/***********************************************************************************
*   Copyright 2021 Marcos Sánchez Torrent.                                         *
*   All Rights Reserved.                                                           *
***********************************************************************************/

#pragma once

#ifndef CORE_EVENT_H
#define CORE_EVENT_H 1

#include "PHAL.h"
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
        uint32 m_LastID = 0;

    public:
        using HandlerType = EventHandler<Args...>;
        using HandlerFunction = typename EventHandlerID<Args...>::HandlerFunction;

        void Connect(HandlerType& handler, HandlerFunction function)
        {
            EventHandlerID<Args...> hnd;
            hnd.Function = std::move(function);
            hnd.ID = m_LastID++;
            handler.m_Event = this;
            handler.m_ID = hnd.ID;
            m_Handlers.push_back(std::move(hnd));
        }

        void Disconnect(HandlerType& handler)
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

        void Trigger(Args&&... args)
        {
            for (EventHandlerID<Args...>& hnd : m_Handlers)
            {
                hnd.Function(std::forward<Args>(args)...);
            }
        }
    };
}

#endif /* CORE_EVENT_H */
