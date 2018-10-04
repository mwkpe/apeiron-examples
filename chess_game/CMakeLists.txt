cmake_minimum_required(VERSION 3.11)
project(chess_game)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-O3 -Wall -Wextra")

include(../apeiron/CMakeLists.txt)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../apeiron/external
    ${CMAKE_CURRENT_SOURCE_DIR}/../apeiron/external/SDL2/x86_64-w64-mingw32/include)

link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../apeiron/external/SDL2/x86_64-w64-mingw32/lib)

add_executable(chess_game
    source/main.cpp
    source/options.cpp
    source/options.h
    source/menu.h
    source/menu.cpp
    source/game.cpp
    source/game.h
    source/tile.h
    source/board.cpp
    source/board.h
    source/piece.cpp
    source/piece.h)

target_link_libraries(chess_game apeiron -lmingw32 -lopengl32 -lSDL2main -lSDL2)
