cmake_minimum_required(VERSION 3.11)
project(point_cloud)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-O3 -Wall -Wextra")

include(../apeiron/CMakeLists.txt)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

if (WIN32)
  include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../apeiron/external/SDL2/x86_64-w64-mingw32/include)
  link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../apeiron/external/SDL2/x86_64-w64-mingw32/lib)
endif ()

add_executable(point_cloud
    source/string_utils.h
    source/main.cpp
    source/point_cloud.cpp
    source/point_cloud.h
    source/world.cpp
    source/world.h)

if (WIN32 AND MINGW)
  target_link_libraries(point_cloud apeiron -lmingw32 -lSDL2main -lSDL2)
elseif (UNIX AND NOT APPLE)
  target_link_libraries(point_cloud apeiron -lSDL2main -lSDL2)
endif ()
