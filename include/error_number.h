// Socket.lua
// Connect to the world!
// @module 'Socket.errno'
// @author Jakit Liang 泊凛
// @date 2023-10-01
// @license MIT

#ifndef SOCKET_LUA_ERROR_NUMBER_H
#define SOCKET_LUA_ERROR_NUMBER_H

#include <lua.hpp>

struct ErrorNumber {
    const char * name;
    int value;
};

int SocketInitError(lua_State *L);

#ifdef _WIN32
int ErrorConvert(int n);
#endif

#endif //SOCKET_LUA_ERROR_NUMBER_H
