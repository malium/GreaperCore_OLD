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
#define WINUSERAPI DECLSPEC_IMPORT
#define WINBASEAPI DECLSPEC_IMPORT

#define WINAPI __stdcall

#define DECLARE_HANDLE(name) struct name##__{int unused;}; typedef struct name##__ *name

typedef long RPC_STATUS;
#	define  RPC_ENTRY __stdcall
#define __RPC_FAR
#define far
#define FAR far

typedef struct _GUID {
    unsigned long  Data1;
    unsigned short Data2;
    unsigned short Data3;
    unsigned char  Data4[8];
} GUID;

typedef GUID UUID;
#define CONST               const
typedef int                 INT;
typedef int                 BOOL;
typedef __int64 INT_PTR, *PINT_PTR;
typedef unsigned int        UINT;
typedef unsigned int        *PUINT;

typedef char CHAR;
typedef CHAR *PCHAR, *LPCH, *PCH;
typedef CONST CHAR *LPCCH, *PCCH;
typedef CHAR *NPSTR, *LPSTR, *PSTR;
typedef CONST CHAR *LPCSTR, *PCSTR;

typedef wchar_t WCHAR;
typedef WCHAR *PWCHAR, *LPWCH, *PWCH;
typedef CONST WCHAR *LPCWCH, *PCWCH;
typedef WCHAR *NWPSTR, *LPWSTR, *PWSTR; 
typedef CONST WCHAR *LPCWSTR, *PCWSTR;
typedef CONST WCHAR *LPCWCHAR, *PCWCHAR;



typedef INT_PTR (FAR WINAPI *FARPROC)();

#define MB_ICONHAND                 0x00000010L
#define MB_ICONERROR                MB_ICONHAND
#define MB_ABORTRETRYIGNORE         0x00000002L
#define MB_OK                       0x00000000L
#define MB_TASKMODAL                0x00002000L
#define MB_TOPMOST                  0x00040000L
#define IDRETRY             4
#define IDIGNORE            5

DECLARE_HANDLE(HWND);
DECLARE_HANDLE(HINSTANCE);
typedef HINSTANCE HMODULE;

RPCRTAPI
RPC_STATUS
RPC_ENTRY
UuidCreate(
    UUID __RPC_FAR* Uuid
);


WINUSERAPI
int
WINAPI
MessageBoxA(
    HWND hWnd,
    LPCSTR lpText,
    LPCSTR lpCaption,
    UINT uType);

WINBASEAPI
FARPROC
WINAPI
GetProcAddress(
    HMODULE hModule,
    LPCSTR lpProcName
    );

WINBASEAPI
HMODULE
WINAPI
LoadLibraryW(
    LPCWSTR lpLibFileName
    );

WINBASEAPI
BOOL
WINAPI
FreeLibrary(
    HMODULE hLibModule
    );


#else
#include <Windows.h>
#include <rpc.h>
#endif
