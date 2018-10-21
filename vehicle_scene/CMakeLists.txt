cmake_minimum_required(VERSION 3.11)
project(vehicle_scene)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-O3 -Wall -Wextra")

include(../apeiron/CMakeLists.txt)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

if (WIN32)
  include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../apeiron/external/SDL2/x86_64-w64-mingw32/include)
  link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../apeiron/external/SDL2/x86_64-w64-mingw32/lib)
endif ()

add_executable(vehicle_scene
    source/main.cpp
    source/options.cpp
    source/options.h
    source/menu.h
    source/menu.cpp
    source/world.cpp
    source/world.h
    source/vehicle.cpp
    source/vehicle.h
    source/road.cpp
    source/road.h
    source/lane_markings.cpp
    source/lane_markings.h)

if (WIN32 AND MINGW)
  target_link_libraries(vehicle_scene apeiron -lmingw32 -lSDL2main -lSDL2)
elseif (UNIX AND NOT APPLE)
  target_link_libraries(vehicle_scene apeiron -lSDL2main -lSDL2)
endif ()
