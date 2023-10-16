// Socket.lua
// Connect to the world!
// FIPS 180-1 compliant SHA-1 implementation
// @module 'Socket.sha1'
// @author Jakit Liang 泊凛, Christophe Devine <devine@cr0.net>
// @date 2023-10-01
// @license GPL

#ifndef SOCKET_LUA_SHA1_H
#define SOCKET_LUA_SHA1_H

#include "basic.h"

struct sha1_context
{
    UInt32 total[2];
    UInt32 state[5];
    UInt8 buffer[64];
};

void sha1_starts( struct sha1_context *ctx );
void sha1_update( struct sha1_context *ctx, const UInt8 *input, UInt32 length);
void sha1_finish( struct sha1_context *ctx, UInt8 digest[20] );

#endif //SOCKET_LUA_SHA1_H
