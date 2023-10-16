
# Socket.lua

> Connect you to the world!

## Intro

This library provides **CROSS PLATFORM** basic Socket API.

People can use this basic library doing their own up layer network things.

## Why Socket.lua

### The Purpose

The reason make this library is to fulfill the absent of Socket in Lua.

A good standard network library in the STL of any language like Ruby & Python is simple.

Having no Characteristics and Prejudice so let developers freely code with their style as they want.

### KISS

> Keep it simple and stupid.

Less code means less bugs.

Keep basic API and platform-specific wrapping. You can make your own up layer network architecture.

There is almost no encapsulation, you can work your own.

### Less bugs

As many developers can see. There is too many bugs in `luasocket`.

It is hard to change the behavior of a large library.

## APIs & Usage

| Name                                          | Desc                                 | Return                                     |
|-----------------------------------------------|--------------------------------------|--------------------------------------------|
| Socket.errno                                  | Error numbers<br/>(Class method)     | table                                      |
| Socket.TCP                                    | Create TCP Socket<br/>(Class method) | Socket                                     |
| Socket.UDP                                    | Create UDP Socket<br/>(Class method) | Socket                                     |
| Socket:connect(ip, port)                      | Connect to remote                    | number                                     |
| Socket:bind(ip, port)                         | Bind address                         | number                                     |
| Socket:listen(size)                           | Listen                               | number                                     |
| Socket:receive(size)                          | Receive data                         | string, number (err)                       |
| Socket:receiveNow(size)                       | Receive data (NonBlock)              | string, number (err)                       |
| Socket:send(data, size)                       | Send data                            | number (Sent count),<br/>number (err)      |
| Socket:sendNow(data, size)                    | Send data (NonBlock)                 | number (Sent count),<br/>number (err)      |
| Socket:close()                                | Close socket                         | number (err)                               |
| Socket:isClosed()                             | Check socket available               | boolean                                    |
| Socket:Select(readArray, writeArray, timeout) | Select sockets<br/>(Class method)    | readableArray, writableArray, number (err) |
| Socket:getAddress()                           | Get socket address                   | string(host), number(port)                 |
| Socket:sha1(string)                           | SHA1 crypto                          | string                                     |
| Socket:sha1hex(string)                        | SHA1 hex crypto                      | string                                     |
| Socket:base64encode(string)                   | Base64 encode                        | string                                     |
| Socket:base64decode(string)                   | Base64 decode                        | string                                     |

## Copyright

> Generate electricity by Jakit with love.

This module is MIT-Licensed.

## Issue

Drop ticket to `issue` if you got any problems.
