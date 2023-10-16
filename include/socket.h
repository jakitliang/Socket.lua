// Socket.lua
// Connect to the world!
// @module 'Socket'
// @author Jakit Liang 泊凛
// @date 2023-10-01
// @license MIT

#ifndef SOCKET_LUA_SOCKET_H
#define SOCKET_LUA_SOCKET_H

#include "basic.h"
#include <lua.hpp>
#if _WIN32
#include <winsock2.h>
#else
#include <sys/select.h>
#endif

struct Socket {
    Byte isNonblock;
    Byte impl[128];

    static void Init(Socket * socket);

    static int TCP(Socket * socket);
    static int UDP(Socket * socket);

    static void GetAddress(Socket * socket, char * address, int len, UInt16 * port);

    static int Connect(Socket * socket, const char * host, UInt64 port);
    static int ConnectNow(Socket * socket, const char * host, UInt64 port);

    static int Bind(Socket * socket, const char * host, UInt64 port);

    static int Listen(Socket * socket, Int32 queue);

    static int Accept(Socket * socket, Socket * clientSocket);
    static int AcceptNow(Socket * socket, Socket * clientSocket);

    static Int64 Receive(Socket * socket, void *buffer, UInt64 size);
    static Int64 ReceiveNow(Socket * socket, void *buffer, UInt64 size);

    static Int64 Send(Socket * socket, const void *buffer, UInt64 size);
    static Int64 SendNow(Socket * socket, const void *buffer, UInt64 size);

    static int Shutdown(Socket * socket, int how);

    static int Close(Socket * socket);

    static int SetNonBlock(Socket *socket);

    static int SetBlock(Socket *socket);

    static int Select(int max, fd_set * rSet, fd_set * wSet, fd_set * eSet, double timeout);

    static int GetError();

    static int IsClosed(Socket *socket);
};

int TableToFDSet(lua_State *L, int idx, fd_set *s);

int FDSetToTable(lua_State *L, int idx, fd_set *s, int maxfd);

#endif //SOCKET_LUA_SOCKET_H
