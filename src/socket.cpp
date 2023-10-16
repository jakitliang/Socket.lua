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
#include <ctype.h>
#include <iostream>

extern "C" {
#include "base64.h"
#include "sha1.h"
};

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

int SocketGetAddress(lua_State *L) {
    auto socket = static_cast<Socket *>(lua_touserdata(L, 1));
    char address[1024]{0};
    UInt16 port = 0;
    Socket::GetAddress(socket, address, 1023, &port);

    lua_pushstring(L, address);
    lua_pushinteger(L, port);

    return 2;
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
    auto ret = Socket::AcceptNow(socket, &client);
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
        err = ECONNRESET;
        lua_pushstring(L, "");

    } else {
        err = Socket::GetError();
        lua_pushstring(L, "");
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
        err = ECONNRESET;
        lua_pushstring(L, "");

    } else {
        err = Socket::GetError();
        lua_pushstring(L, "");
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
        lua_pushinteger(L, 0);
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
        lua_pushinteger(L, 0);
    }

    lua_pushinteger(L, err);

    return 2;
}

int SocketClose(lua_State *L) {
    auto socket = static_cast<Socket *>(lua_touserdata(L, 1));
    auto ret = Socket::Close(socket);
    int err = 0;

    if (ret == 0) {
        lua_pushinteger(L, ret);

    } else {
        err = Socket::GetError();
        lua_pushinteger(L, err);
    }

    return 1;
}

int SocketSelect(lua_State *L) {
    fd_set r{}, w{};
    int max = -1, maxfd = -1;
    Byte getR = 0, getW = 0;
    FD_ZERO(&r);
    FD_ZERO(&w);
    if (lua_istable(L, 1)) {
        if (lua_objlen(L, 1) > 0) {
            max = TableToFDSet(L, 1, &r);
            maxfd = max > maxfd ? max : maxfd;
            getR = 1;
        }
    }
    if (lua_istable(L, 2)) {
        if (lua_objlen(L, 2) > 0) {
            max = TableToFDSet(L, 2, &w);
            maxfd = max > maxfd ? max : maxfd;
            getW = 1;
        }
    }
    auto timeout = luaL_optnumber(L, 3, -1);

#ifdef _WIN32
    int ret = Socket::Select(maxfd + 1,
                             &r,
                             getW ? &w : nullptr,
                             nullptr,
                             timeout);
#else
    int ret = Socket::Select(maxfd + 1,
                             getR ? &r : nullptr,
                             getW ? &w : nullptr,
                             nullptr,
                             timeout);
#endif

    FDSetToTable(L, 1, &r, maxfd);
    FDSetToTable(L, 2, &w, maxfd);

    if (ret == -1) {
        ret = Socket::GetError();
    }

    lua_pushinteger(L, ret);

    return 3;
}

int SocketIsClosed(lua_State *L) {
    auto socket = static_cast<Socket *>(lua_touserdata(L, 1));
    auto ret = Socket::IsClosed(socket);

    if (ret == 0) {
        lua_pushboolean(L, 1);

    } else {
        lua_pushboolean(L, 0);
    }

    return 1;
}

int SocketToString(lua_State *L) {
    auto socket = static_cast<Socket *>(lua_touserdata(L, 1));
    lua_pushfstring(L, "Socket: %p", socket);

    return 1;
}

int SocketGC(lua_State *L) {
    auto socket = static_cast<Socket *>(lua_touserdata(L, 1));
    Socket::Close(socket);

    return 0;
}

int SocketBase64Encode(lua_State *L) {
    auto origin = luaL_checkstring(L, 1);
    auto size_origin = strlen(origin);
    int sizeEncoded = base64encode_len(size_origin);
    char * encoded = new char[sizeEncoded + 1]{0};

    bool ret = base64encode(
            reinterpret_cast<const unsigned char *>(origin),
            size_origin,
            encoded,
            &sizeEncoded);

    if (ret) {
        lua_pushstring(L, encoded);

    } else {
        lua_pushnil(L);
    }

    delete[] encoded;

    return 1;
}

int SocketBase64Decode(lua_State *L) {
    auto encoded = luaL_checkstring(L, 1);
    auto sizeEncoded = strlen(encoded);
    int sizeDecoded = base64decode_len(encoded, sizeEncoded);
    char * decoded = new char[sizeDecoded + 1]{0};

    bool ret = base64decode(
            encoded,
            sizeEncoded,
            reinterpret_cast<unsigned char *>(decoded),
            &sizeDecoded);

    if (ret) {
        lua_pushstring(L, decoded);

    } else {
        lua_pushnil(L);
    }

    delete[] decoded;

    return 1;
}

static char nr2char(int n) {
    if (0 <= n && n <= 9) {
        return '0' + n;
    } else {
        return 'a' + n - 10;
    }
}

int SocketSHA1(lua_State *L) {
    unsigned char digest[21]{0};
    int i;
    sha1_context ctx{};
    auto str = luaL_checkstring(L, 1);

    memset(&ctx, 0, sizeof(sha1_context));
    sha1_starts(&ctx);
    sha1_update(&ctx, reinterpret_cast<const UInt8 *>(str), strlen(str));
    sha1_finish(&ctx, reinterpret_cast<UInt8 *>(&digest));

    lua_pushstring(L, reinterpret_cast<char *>(digest));

    return 1;
}

int SocketSHA1Hex(lua_State *L) {
    unsigned char digest[21]{0};
    char digest_hex[41]{0};
    int i;
    sha1_context ctx{};
    auto str = luaL_checkstring(L, 1);
    
    memset(&ctx, 0, sizeof(sha1_context));
    sha1_starts(&ctx);
    sha1_update(&ctx, reinterpret_cast<const UInt8 *>(str), strlen(str));
    sha1_finish(&ctx, reinterpret_cast<UInt8 *>(&digest));

    for (i = 0; i < 20; i++) {
        digest_hex[i*2+0] = nr2char((digest[i] >> 4) & 0xf);
        digest_hex[i*2+1] = nr2char(digest[i] & 0x0f);
    }

    lua_pushstring(L, digest_hex);

    return 1;
}

const struct luaL_Reg lib[] = {
        {"TCP", SocketTCP},
        {"UDP", SocketUDP},
        {"getAddress", SocketGetAddress},
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
        {"isClosed", SocketIsClosed},
        {"base64encode", SocketBase64Encode},
        {"base64decode", SocketBase64Decode},
        {"sha1hex", SocketSHA1Hex},
        {"sha1", SocketSHA1},
        {"__tostring", SocketToString},
        {"__gc", SocketGC},
        {0,0}
};

Socket * SocketNew(lua_State *L) {
    auto socket = static_cast<Socket *>(lua_newuserdata(L, sizeof(Socket)));
    Socket::Init(socket);
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
    lua_setfield(L, -2, "Errno");
    lua_pushinteger(L, 0);
    lua_setfield(L, -2, "OK");
    return 1;
}
}
