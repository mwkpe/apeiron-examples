cmake_minimum_required(VERSION 3.11)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-O3 -Wall -Wextra")

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../apeiron/cmake")
include(apeiron)

project(point_cloud_vr)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../apeiron/external/SDL2/x86_64-w64-mingw32/include
    ${CMAKE_CURRENT_SOURCE_DIR}/source/external/openvr)

link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../apeiron/external/SDL2/x86_64-w64-mingw32/lib
    ${CMAKE_CURRENT_SOURCE_DIR}/source/external/openvr)

add_executable(point_cloud_vr
    source/string_utils.h
    source/main.cpp
    source/hmd.cpp
    source/hmd.h
    source/point_cloud.cpp
    source/point_cloud.h
    source/world.cpp
    source/world.h)

target_link_libraries(point_cloud_vr apeiron -lmingw32 -lSDL2main -lSDL2 -lopenvr_api)
