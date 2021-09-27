/***********************************************************************************
*   Copyright 2021 Marcos Sánchez Torrent.                                         *
*   All Rights Reserved.                                                           *
***********************************************************************************/

#pragma once

#ifndef CORE_TASK_H
#define CORE_TASK_H 1

#include "../Memory.h"
#include <functional>

namespace greaper
{
	class Task
	{
		Duration_t Duration;

	public:
		std::function<void()> Function;
		StringView Name;

		explicit Task(const std::function<void()>& function = nullptr, const StringView& name = "unnamed"sv)
			:Function(function)
			, Name(name)
			, Duration(0)
		{

		}

		void operator()()
		{
			VerifyNotNull(Function, "Trying to execute a nullptr task");
			const auto before = Clock_t::now();
			Function();
			const auto after = Clock_t::now();
			Duration = after - before;
			const auto dur = static_cast<double>(Duration.count());
			String msg;
			if (dur > 1e9)
			{
				msg = Format("Task '%s' took %fs.", Name.data(), dur * 1e-9);
			}
			else if (dur > 1e6)
			{
				msg = Format("Task '%s' took %fms.", Name.data(), dur * 1e-6);
			}
			else if (dur > 1e3)
			{
				msg = Format("Task '%s' took %fµs.", Name.data(), dur * 1e-3);
			}
			else
			{
				msg = Format("Task '%s' took %fns.", Name.data(), dur);
			}
#if PLT_WINDOWS
			OutputDebugStringA(msg.c_str());
#else
			printf(msg.c_str());
#endif
		}

		Duration_t GetTaskDuration()const noexcept
		{
			return Duration;
		}
	};
}

#endif /* CORE_TASK_H */