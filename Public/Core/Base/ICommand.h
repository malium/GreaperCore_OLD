/***********************************************************************************
*   Copyright 2021 Marcos Sánchez Torrent.                                         *
*   All Rights Reserved.                                                           *
***********************************************************************************/

#pragma once

#ifndef CORE_I_COMMAND_H
#define CORE_I_COMMAND_H 1

#include "../Memory.h"

namespace greaper
{
    struct CommandInfo
    {
        String CommandName;
        StringVec CommandArgs;

        static CommandInfo FromConsole(const String& cmdLine);
    };

    class ICommand
    {
    public:
        
    };
}

#endif /* CORE_I_COMMAND_H */