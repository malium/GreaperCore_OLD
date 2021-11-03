/***********************************************************************************
*   Copyright 2021 Marcos Sánchez Torrent.                                         *
*   All Rights Reserved.                                                           *
***********************************************************************************/

#pragma once

#ifndef CORE_I_WINDOW_MANAGER_H
#define CORE_I_WINDOW_MANAGER_H 1

#include "Interface.h"
#include "Base/IWindow.h"
#include "Result.h"

namespace greaper
{
	class IWindowManager : public TInterface<IWindowManager>
	{
	public:
		static constexpr Uuid InterfaceUUID = Uuid{ 0x9FFF5170, 0x9A5E4E9C, 0x9CFD0FAB, 0xBF2C3E75 };
		static constexpr StringView InterfaceName = "WindowManager"sv;

		virtual ~IWindowManager()noexcept = default;

		virtual Result<IWindow*> CreateWindow(const WindowDesc& desc = {}) = 0;

		virtual EmptyResult DestroyWindow(IWindow* window) = 0;

		virtual Result<IWindow*> FindWindow(const WString& title)const = 0;

		virtual Vector<IWindow*> GetWindows()const = 0;
	};
}

#endif /* CORE_I_WINDOW_MANAGER_H */