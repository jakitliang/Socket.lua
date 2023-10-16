// Socket.lua
// Connect to the world!
// @module 'Socket'
// @author Jakit Liang 泊凛
// @date 2023-10-01
// @license MIT

#ifndef SOCKET_LUA_BASIC_H
#define SOCKET_LUA_BASIC_H

typedef char Int8;
typedef unsigned char UInt8;
typedef short Int16;
typedef unsigned short UInt16;
typedef int Int32;
typedef unsigned int UInt32;
typedef long long Int64;
typedef unsigned long long UInt64;
typedef UInt8 Byte;
typedef Int64 Integer;
typedef UInt64 UInteger;
typedef UInt64 Size;
typedef Int64 SSize;

#if _WIN64
typedef unsigned long long Pointer;
#elif _WIN32
typedef unsigned int Pointer;
#else
typedef unsigned long long Pointer;
#endif

#ifdef _WIN32
#define SOCKET_API __declspec(dllexport)
#define SOCKET_DECL __cdecl
#else
#define SOCKET_API __attribute__((visibility("default")))
#define SOCKET_DECL __cdecl
#endif

#endif //SOCKET_LUA_BASIC_H
