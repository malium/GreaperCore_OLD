/***********************************************************************************
*   Copyright 2021 Marcos Sánchez Torrent.                                         *
*   All Rights Reserved.                                                           *
***********************************************************************************/

#pragma once

#ifndef CORE_I_WINDOW_H
#define CORE_I_WINDOW_H 1

#include "../Memory.h"
#include "Rect.h"
#include "IThread.h"

namespace greaper
{
    class IWindow
    {
    public:
        using Position_t = std::pair<int32, int32>;
        using Size_t = std::pair<uint32, uint32>;

        virtual ~IWindow() = default;

        virtual Position_t GetWindowPosition()const = 0;

        virtual Size_t GetWindowSize()const = 0;

        virtual RectI GetNCWindowRect()const = 0;

        virtual RectU GetWindowRect()const = 0;

        virtual void Maximize() = 0;

        virtual void Minimize() = 0;

        virtual void Restore() = 0;

        virtual void SetWindowPosition(const Position_t& position) = 0;

        virtual void SetWindowSize(const Size_t& size) = 0;

        virtual void SetTitle(const WString& title) = 0;

        virtual const WString& GetTitle()const = 0;

        virtual bool IsFocused()const = 0;

        virtual void RequestWindowFocus() = 0;

        virtual void EnableCursor(bool enable) = 0;

        virtual bool IsCursorEnabled()const = 0;

        virtual ThreadID_t GetThreadID()const = 0;

        virtual void SetActive(bool active) = 0;            

        virtual bool IsActive()const = 0;
    };
}

#endif /* CORE_I_WINDOW_H */