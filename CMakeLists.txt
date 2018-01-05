cmake_minimum_required(VERSION 2.6)

project(muduo-lua CXX)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "debug")
endif()

if(NOT MUDUO_PATH)
  set(MUDUO_PATH "$ENV{HOME}/build/${CMAKE_BUILD_TYPE}-install")
endif()

set(CXX_FLAGS
 -g
 # -DVALGRIND
 # -DMUDUO_STD_STRING
 -DLUA_COMPAT_ALL
 -DLUA_USE_LINUX
 -Wall
 -Wextra
 # -m32
 -Werror
 -Wconversion
 -Wno-unused-parameter
 -Wold-style-cast
 -Woverloaded-virtual
 -Wpointer-arith
 -Wshadow
 -Wwrite-strings
 -march=native
 # -MMD
 # -std=c++0x
 -rdynamic
 )
string(REPLACE ";" " " CMAKE_CXX_FLAGS "${CXX_FLAGS}")

# set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAGS_DEBUG "-O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG")
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

find_path(Muduo_INCLUDE_DIR muduo "${MUDUO_PATH}/include")
find_path(Muduo_LIBRARY_DIR libmuduo_net.a "${MUDUO_PATH}/lib")
set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} ${Muduo_LIBRARY_DIR})
message(STATUS ${Muduo_INCLUDE_DIR})
message(STATUS ${Muduo_LIBRARY_DIR})

include_directories(${Muduo_INCLUDE_DIR})
find_library(muduo_base muduo_base)
find_library(muduo_net muduo_net)
find_library(muduo_http muduo_http)
find_library(muduo_inspect muduo_inspect)
message(STATUS ${muduo_base})
message(STATUS ${muduo_net})

find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

find_package(Lua REQUIRED)
message(STATUS "Found Lua ${LUA_VERSION_STRING} in ${LUA_INCLUDE_DIR}")
include_directories(${LUA_INCLUDE_DIR})

# TODO: if not found, build our own ?

include_directories(${PROJECT_SOURCE_DIR})

add_subdirectory(hello)
add_subdirectory(world)

