// Socket.lua
// Connect to the world!
// @module 'Socket'
// @author Jakit Liang 泊凛
// @date 2023-10-01
// @license MIT

#define LUA_LIB
#include <lua.hpp>
#include "socket.h"
#include "error_number.h"
#include <cstring>
#include <iostream>

#define LIB_NAME "socket"

Socket * SocketNew(lua_State *L);

int SocketTCP(lua_State *L) {
    auto socket = SocketNew(L);
    auto ret = Socket::TCP(socket);

    if (ret == -1) {
        lua_pushinteger(L, Socket::GetError());
        return 2;
    }

    return 1;
}

int SocketUDP(lua_State *L) {
    auto socket = SocketNew(L);
    auto ret = Socket::UDP(socket);

    if (ret == -1) {
        lua_pushinteger(L, Socket::GetError());
        return 2;
    }

    return 1;
}

int SocketConnect(lua_State *L) {
    auto socket = static_cast<Socket *>(lua_touserdata(L, 1));
    auto host = luaL_checkstring(L, 2);
    auto port = luaL_checkinteger(L, 3);

    auto ret = Socket::Connect(socket, host, port);
    int err = 0;

    if (ret == -1) {
        err = Socket::GetError();
    }

    lua_pushinteger(L, err);
    return 1;
}

int SocketConnectNow(lua_State *L) {
    auto socket = static_cast<Socket *>(lua_touserdata(L, 1));
    auto host = luaL_checkstring(L, 2);
    auto port = luaL_checkinteger(L, 3);

    auto ret = Socket::ConnectNow(socket, host, port);
    int err = 0;

    if (ret == -1) {
        err = Socket::GetError();
    }

    lua_pushinteger(L, err);
    return 1;
}

int SocketBind(lua_State *L) {
    auto socket = static_cast<Socket *>(lua_touserdata(L, 1));
    auto host = luaL_checkstring(L, 2);
    auto port = luaL_checkinteger(L, 3);

    auto ret = Socket::Bind(socket, host, port);
    int err = 0;

    if (ret == -1) {
        err = Socket::GetError();
    }

    lua_pushinteger(L, err);
    return 1;
}

int SocketListen(lua_State *L) {
    auto socket = static_cast<Socket *>(lua_touserdata(L, 1));
    auto count = luaL_checkinteger(L, 2);

    auto ret = Socket::Listen(socket, count);
    int err = 0;

    if (ret == -1) {
        err = Socket::GetError();
    }

    lua_pushinteger(L, err);
    return 1;
}

int SocketAccept(lua_State *L) {
    auto socket = static_cast<Socket *>(lua_touserdata(L, 1));
    std::cout << "SocketAccept begin" << std::endl;

    Socket client{0,{0}};
    auto ret = Socket::Accept(socket, &client);
    int err = 0;

    if (ret >= 0) {
        auto clientSocket = SocketNew(L);
        memcpy(clientSocket, &client, sizeof(Socket));

    } else {
        err = Socket::GetError();
        lua_pushnil(L);
    }

    lua_pushinteger(L, err);

    return 2;
}

int SocketAcceptNow(lua_State *L) {
    auto socket = static_cast<Socket *>(lua_touserdata(L, 1));

    Socket client{0,{0}};
    auto ret = Socket::Accept(socket, &client);
    int err = 0;

    if (ret >= 0) {
        auto clientSocket = SocketNew(L);
        memcpy(clientSocket, &client, sizeof(Socket));

    } else {
        err = Socket::GetError();
        lua_pushnil(L);
    }

    lua_pushinteger(L, err);

    return 2;
}

int SocketReceive(lua_State *L) {
    auto socket = static_cast<Socket *>(lua_touserdata(L, 1));
    auto size = luaL_checkinteger(L, 2);
    Byte * buffer = new Byte[size + 1]{0};

    auto ret = Socket::Receive(socket, buffer, size);
    int err = 0;

    if (ret > 0) {
        lua_pushstring(L, reinterpret_cast<char *>(buffer));

    } else if (ret == 0) {
#ifdef _WIN32
        err = 108;
#else
        err = Socket::GetError();
#endif
        lua_pushstring(L, "");

    } else {
        err = Socket::GetError();
        lua_pushnil(L);
    }

    lua_pushinteger(L, err);

    return 2;
}

int SocketReceiveNow(lua_State *L) {
    auto socket = static_cast<Socket *>(lua_touserdata(L, 1));
    auto size = luaL_checkinteger(L, 2);
    Byte * buffer = new Byte[size + 1]{0};

    auto ret = Socket::ReceiveNow(socket, buffer, size);
    int err = 0;

    if (ret > 0) {
        lua_pushstring(L, reinterpret_cast<char *>(buffer));

    } else if (ret == 0) {
#ifdef _WIN32
        err = 108;
#else
        err = Socket::GetError();
#endif
        lua_pushstring(L, "");

    } else {
        err = Socket::GetError();
        lua_pushnil(L);
    }

    lua_pushinteger(L, err);

    return 2;
}

int SocketSend(lua_State *L) {
    auto socket = static_cast<Socket *>(lua_touserdata(L, 1));
    auto buffer = luaL_checkstring(L, 2);
    auto size = luaL_checkinteger(L, 3);

    auto ret = Socket::Send(socket, buffer, size);
    int err = 0;

    if (ret >= 0) {
        lua_pushinteger(L, ret);

    } else {
        err = Socket::GetError();
        lua_pushnil(L);
    }

    lua_pushinteger(L, err);

    return 2;
}

int SocketSendNow(lua_State *L) {
    auto socket = static_cast<Socket *>(lua_touserdata(L, 1));
    auto buffer = luaL_checkstring(L, 2);
    auto size = luaL_checkinteger(L, 3);

    auto ret = Socket::SendNow(socket, buffer, size);
    int err = 0;

    if (ret >= 0) {
        lua_pushinteger(L, ret);

    } else {
        err = Socket::GetError();
        lua_pushnil(L);
    }

    lua_pushinteger(L, err);

    return 2;
}

int SocketClose(lua_State *L) {
    auto socket = static_cast<Socket *>(lua_touserdata(L, 1));
    auto ret = Socket::Close(socket);

    lua_pushinteger(L, ret);

    return 1;
}

int SocketSelect(lua_State *L) {
    fd_set r{}, w{};
    int max = -1, maxfd = -1;
    Byte getR = 0, getW = 0;
    FD_ZERO(&r);
    FD_ZERO(&w);
    if (lua_istable(L, 1)) {
        max = TableToFDSet(L, 1, &r);
        maxfd = max > maxfd ? max : maxfd;
        getR = 1;
    }
    if (lua_istable(L, 2)) {
        max = TableToFDSet(L, 2, &w);
        maxfd = max > maxfd ? max : maxfd;
        getW = 1;
    }
    auto timeout = luaL_optnumber(L, 3, -1);

    int ret = Socket::Select(maxfd + 1,
                             getR ? &r : nullptr,
                             getW ? &w : nullptr,
                             nullptr,
                             timeout);

    FDSetToTable(L, 1, &r, maxfd);
    FDSetToTable(L, 2, &w, maxfd);

    lua_pushinteger(L, ret);

    return 3;
}

int SocketGC(lua_State *L) {
    auto socket = static_cast<Socket *>(lua_touserdata(L, 1));
    Socket::Close(socket);

    return 0;
}

const struct luaL_Reg lib[] = {
        {"TCP", SocketTCP},
        {"UDP", SocketUDP},
        {"connect", SocketConnect},
        {"connectNow", SocketConnectNow},
        {"bind", SocketBind},
        {"listen", SocketListen},
        {"accept", SocketAccept},
        {"acceptNow", SocketAcceptNow},
        {"receive", SocketReceive},
        {"receiveNow", SocketReceiveNow},
        {"send", SocketSend},
        {"sendNow", SocketSendNow},
        {"close", SocketClose},
        {"Select", SocketSelect},
        {"__gc", SocketGC},
        {0,0}
};

Socket * SocketNew(lua_State *L) {
    auto socket = static_cast<Socket *>(lua_newuserdata(L, sizeof(Socket)));
    memset(socket, 0, sizeof(Socket));
    lua_newtable(L);
    luaL_setfuncs(L, lib, 0);
    lua_pushliteral(L, "__index");
    lua_pushvalue(L, -2);               /* dup methods table*/
    lua_rawset(L, -1);                  /* metatable.__index = methods */
    lua_setmetatable(L, -2);
    return socket;
}

extern "C" {
SOCKET_API int luaopen_socket(lua_State *L)
{
    lua_newtable(L);
    luaL_setfuncs(L, lib, 0);
    SocketInitError(L);
    lua_setfield(L, -2, "errno");
    return 1;
}
}
