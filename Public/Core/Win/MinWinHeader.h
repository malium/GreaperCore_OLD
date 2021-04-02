/***********************************************************************************
*   Copyright 2021 Marcos Sánchez Torrent.                                         *
*   All Rights Reserved.                                                           *
***********************************************************************************/

#pragma once

#pragma comment(lib, "Rpcrt4.lib")
#pragma comment(lib, "uuid.lib")

#if true
#define DECLSPEC_IMPORT __declspec(dllimport)
#define RPCRTAPI DECLSPEC_IMPORT
typedef long RPC_STATUS;
#	define  RPC_ENTRY __stdcall
#define __RPC_FAR

typedef struct _GUID {
    unsigned long  Data1;
    unsigned short Data2;
    unsigned short Data3;
    unsigned char  Data4[8];
} GUID;

typedef GUID UUID;



RPCRTAPI
RPC_STATUS
RPC_ENTRY
UuidCreate(
    UUID __RPC_FAR* Uuid
);

#else
#include <Windows.h>
#include <rpc.h>
#endif
