// Socket.lua
// Connect to the world!
// @module 'Socket'
// @author Jakit Liang 泊凛
// @date 2023-10-01
// @license MIT

#include "socket.h"
#include "socket_mswin.h"
#include <cmath>
#include <ws2tcpip.h>
#include <iostream>
#include <cstdlib>
#include "error_number.h"

static WSADATA wsaData;
static WORD wVersionRequested = MAKEWORD(2, 2);
static bool wsaStartUp = false;
static SOCKET defaultSocket;

void onExit() {
    closesocket(defaultSocket);
    WSACleanup();
}

bool checkStart() {
    if (!wsaStartUp) {
        int err = WSAStartup(wVersionRequested, &wsaData);
        if (err != 0) return false;
        atexit(onExit);
        defaultSocket = socket(AF_UNSPEC, SOCK_RAW, IPPROTO_ICMP);
        wsaStartUp = true;
    }

    return wsaStartUp;
}

SocketImpl * SocketCast(Socket *socket) {
    return reinterpret_cast<SocketImpl *>(socket->impl);
}

void Socket::Init(Socket * socket) {
    auto impl = SocketCast(socket);
    memset(socket, 0, sizeof(Socket));
    impl->fd = INVALID_SOCKET;
}

int Socket::TCP(Socket *socket) {
    auto impl = SocketCast(socket);
    if (!checkStart()) {
        return -1;
    }

    impl->fd = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (impl->fd == INVALID_SOCKET) {
        return -1;
    }

    return impl->fd;
}

int Socket::UDP(Socket *socket) {
    auto impl = SocketCast(socket);
    if (!checkStart()) {
        return -1;
    }

    impl->fd = ::socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (impl->fd == INVALID_SOCKET) {
        return -1;
    }

    return impl->fd;
}

void Socket::GetAddress(Socket * socket, char * address, int len, UInt16 * port) {
    auto impl = SocketCast(socket);
    inet_ntop(impl->addr.sin_family, &impl->addr.sin_addr, address, len);
    (*port) = htons(impl->addr.sin_port);
}

int Socket::Connect(Socket * socket, const char * host, UInt64 port) {
    auto impl = SocketCast(socket);
    impl->addr.sin_family =  AF_INET;
    impl->addr.sin_addr.s_addr = inet_addr(host);
    impl->addr.sin_port = htons(port);

    return connect(impl->fd, reinterpret_cast<sockaddr *>(&impl->addr), sizeof(impl->addr));
}

int Socket::ConnectNow(Socket *socket, const char *host, UInt64 port) {
    auto impl = SocketCast(socket);
    impl->addr.sin_family =  AF_INET;
    impl->addr.sin_addr.s_addr = inet_addr(host);
    impl->addr.sin_port = htons(port);

    if (socket->isNonblock) {
        return connect(impl->fd, reinterpret_cast<sockaddr *>(&impl->addr), sizeof(impl->addr));
    }

    Socket::SetNonBlock(socket);
    int ret = connect(impl->fd, reinterpret_cast<sockaddr *>(&impl->addr), sizeof(impl->addr));
    Socket::SetBlock(socket);

    return ret;
}

int Socket::Bind(Socket *socket, const char *host, UInt64 port) {
    auto impl = SocketCast(socket);
    impl->addr.sin_family =  AF_INET;
    impl->addr.sin_addr.s_addr = inet_addr(host);
    impl->addr.sin_port = htons(port);

    return bind(impl->fd, reinterpret_cast<sockaddr *>(&impl->addr), sizeof(impl->addr));
}

int Socket::Listen(Socket *socket, Int32 queue) {
    auto impl = SocketCast(socket);
    return listen(impl->fd, queue);
}

int Socket::Accept(Socket *socket, Socket *clientSocket) {
    auto impl = SocketCast(socket);
    auto clientSocketImpl = SocketCast(clientSocket);
    int len = sizeof(clientSocketImpl->addr);
    clientSocketImpl->fd = accept(impl->fd, reinterpret_cast<sockaddr *>(&clientSocketImpl->addr), &len);
    return clientSocketImpl->fd;
}

int Socket::AcceptNow(Socket *socket, Socket *clientSocket) {
    auto impl = SocketCast(socket);
    auto clientSocketImpl = SocketCast(clientSocket);
    int len = sizeof(clientSocketImpl->addr);

    if (socket->isNonblock) {
        clientSocketImpl->fd = accept(impl->fd, reinterpret_cast<sockaddr *>(&clientSocketImpl->addr), &len);
        return clientSocketImpl->fd;
    }

    Socket::SetNonBlock(socket);
    clientSocketImpl->fd = accept(impl->fd, reinterpret_cast<sockaddr *>(&clientSocketImpl->addr), &len);
    Socket::SetBlock(socket);

    return clientSocketImpl->fd;
}

Int64 Socket::Receive(Socket * socket, void *buffer, UInt64 size) {
    auto impl = SocketCast(socket);
    return recv(impl->fd, reinterpret_cast<char *>(buffer), size, 0);
}

Int64 Socket::ReceiveNow(Socket * socket, void *buffer, UInt64 size) {
    auto impl = SocketCast(socket);
    return recv(impl->fd, reinterpret_cast<char *>(buffer), size, MSG_PARTIAL);
}

Int64 Socket::Send(Socket * socket, const void *buffer, UInt64 size) {
    auto impl = SocketCast(socket);
    return send(impl->fd, reinterpret_cast<const char *>(buffer), size, 0);
}

Int64 Socket::SendNow(Socket * socket, const void *buffer, UInt64 size) {
    auto impl = SocketCast(socket);
    return send(impl->fd, reinterpret_cast<const char *>(buffer), size, MSG_PARTIAL);
}

int Socket::Shutdown(Socket *socket, int how) {
    auto impl = SocketCast(socket);
    return shutdown(impl->fd, how);
}

int Socket::Close(Socket *socket) {
    auto impl = SocketCast(socket);
    int ret = 0;

    if (impl->fd != INVALID_SOCKET) {
        ret = closesocket(impl->fd);
        impl->fd = INVALID_SOCKET;
    }

    return ret;
}

int Socket::Select(int max, fd_set * rSet, fd_set * wSet, fd_set * eSet, double timeout) {
    timeval tv{0, 0};
    checkStart();

    tv.tv_sec = floor(timeout);
    tv.tv_usec = (timeout - floor(timeout)) * 1000000;
    FD_SET(defaultSocket, rSet);
    int ret = select(max, rSet, wSet, eSet, &tv);
    FD_CLR(defaultSocket, rSet);
    return ret;
}

int Socket::SetNonBlock(Socket *socket) {
    socket->isNonblock = 1;
    auto impl = SocketCast(socket);
    u_long flag = 1;
    ioctlsocket(impl->fd, FIONBIO, &flag);
    return 0;
}

int Socket::SetBlock(Socket *socket) {
    socket->isNonblock = 0;
    auto impl = SocketCast(socket);
    u_long flag = 0;
    ioctlsocket(impl->fd, FIONBIO, &flag);
    return 0;
}

int Socket::GetError() {
    return ErrorConvert(WSAGetLastError());
}

int Socket::IsClosed(Socket *socket) {
    auto impl = SocketCast(socket);
    return impl->fd == INVALID_SOCKET ? 0 : 1;
}

int TableToFDSet(lua_State *L, int idx, fd_set *s) {
    SOCKET maxfd = 0;

    auto n = lua_objlen(L, idx);
    for (int i = 1; i <= n; ++i) {
        lua_rawgeti(L, idx, i);

        if (lua_isuserdata(L, -1)) {
            auto socket = static_cast<Socket *>(lua_touserdata(L, -1));
            auto impl = SocketCast(socket);
            if (impl->fd != INVALID_SOCKET) {
                FD_SET(impl->fd, s);
                if (impl->fd > maxfd) {
                    maxfd = impl->fd;
                }
            }
        }

        lua_pop(L, 1);
    }

    return maxfd;
}

int PushSocketForFD(lua_State *L, int idx, int fd) {
    auto n = lua_objlen(L, idx);
    for (int i = 1; i <= n; ++i) {
        lua_rawgeti(L, idx, i);

        if (lua_isuserdata(L, -1)) {
            auto socket = static_cast<Socket *>(lua_touserdata(L, -1));
            auto impl = SocketCast(socket);

            if (impl->fd == fd) {
                return 1;
            }
        }

        lua_pop(L, 1);
    }

    return 0;
}

int FDSetToTable(lua_State *L, int idx, fd_set *s, int maxfd) {
    int n = 1;
    lua_newtable(L);

    for (int i = 0; i <= maxfd; ++i) {
        if (FD_ISSET(i, s)) {
            if (PushSocketForFD(L, idx, i)) {
                lua_rawseti(L, -2, n++);

            } else {
                return luaL_error(L, "unexpected file descriptor returned from select");
            }
        }
    }

    return 1;
}

