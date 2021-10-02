/***********************************************************************************
*   Copyright 2021 Marcos Sánchez Torrent.                                         *
*   All Rights Reserved.                                                           *
***********************************************************************************/

#pragma once

#ifndef CORE_I_COMMAND_MANAGER_H
#define CORE_I_COMMAND_MANAGER_H 1

#include "Interface.h"
#include "Base/IConsole.h"
#include "Base/ICommand.h"
#include "Result.h"

namespace greaper
{
    class ICommandManager : public IInterface
    {
    public:
        static constexpr Uuid InterfaceUUID = Uuid{ 0x557FF73A, 0x6C4144AF, 0xB02DE998, 0x0D378CCA };
		static constexpr StringView InterfaceName = StringView{ "CommandManager" };

        virtual ~ICommandManager() = default;

        virtual void HandleCommand(const CommandInfo& info) = 0;

        virtual void UndoLastCommand() = 0;

        virtual void UndoCommand(const String& cmdName) = 0;

        virtual EmptyResult AddCommand(ICommand* cmd) = 0;

        virtual EmptyResult RemoveCommand(const String& cmdName) = 0;

        virtual Result<ICommand*> GetCommand(const String& cmdName) = 0;

        virtual bool HasCommand(const String& cmdName)const = 0;

        virtual sizet GetStackedCommandCount()const = 0;

        virtual EmptyResult EnableConsole(bool enable) = 0;

        virtual bool IsConsoleEnabled()const = 0;

        virtual Result<IConsole*> GetConsole()const = 0;
    };
}

#endif /* CORE_I_COMMAND_MANAGER_H */