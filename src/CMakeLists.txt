# Socket.lua
# Connect to the world!
# @author Jakit Liang 泊凛
# @date 2023-10-01
# @license MIT

if(CMAKE_SYSTEM_NAME MATCHES "Darwin")
#    set(LUA_DIR "~/Documents/Projects/LuaJIT/build")
    include_directories(${LUA_DIR}/include/luajit-2.1)
    find_library(LUA_LIB NAMES luajit-5.1 luajit PATHS ${LUA_DIR}/lib)
    add_library(socket SHARED socket.cpp socket_posix.cpp
            socket_posix.h error_number_posix.cpp base64.c sha1.c)
    target_link_libraries(socket ${LUA_LIB})

elseif(CMAKE_SYSTEM_NAME MATCHES "Windows")
    set(MY_PRODUCT_NUMBER 0)
    set(MY_PRODUCT_VERSION 1)
    set(MY_BUILD_NUMBER 5)

    configure_file(
            ${CMAKE_CURRENT_SOURCE_DIR}/version.rc.in
            ${CMAKE_CURRENT_BINARY_DIR}/version.rc
            @ONLY)

    include_directories(${LUA_DIR}\\include\\luajit-2.1)
    find_library(LUA_LIB NAMES luajit-5.1 luajit lua51 PATHS ${LUA_DIR}/lib)
    find_library(WIN_SOCK_LIB ws2_32)
    add_library(socket SHARED
            socket.cpp socket_mswin.cpp socket_mswin.h
            error_number_mswin.cpp
            base64.c sha1.c
            ${CMAKE_CURRENT_BINARY_DIR}/version.rc)
    target_link_libraries(socket ${LUA_LIB} ${WIN_SOCK_LIB})

elseif(CMAKE_SYSTEM_NAME MATCHES "Linux")
    include_directories(${LUA_DIR}/include/luajit-2.1)
    find_library(LUA_LIB NAMES luajit-5.1 luajit PATHS ${LUA_DIR}/lib)
    add_library(socket SHARED socket.cpp socket_posix.cpp socket_posix.h
            error_number_posix.cpp base64.c sha1.c)
    target_link_libraries(socket ${LUA_LIB})
endif()
