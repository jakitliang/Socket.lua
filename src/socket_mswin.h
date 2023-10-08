// Socket.lua
// Connect to the world!
// @module 'Socket'
// @author Jakit Liang 泊凛
// @date 2023-10-01
// @license MIT

#ifndef SOCKET_LUA_SOCKET_MSWIN_H
#define SOCKET_LUA_SOCKET_MSWIN_H

#include <winsock2.h>

struct SocketImpl {
    SOCKET fd;
    sockaddr_in addr;
};

#endif //SOCKET_LUA_SOCKET_MSWIN_H
