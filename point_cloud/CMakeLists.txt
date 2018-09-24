cmake_minimum_required(VERSION 3.10)
project(point_cloud)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-O3 -Wall -Wextra -pedantic-errors")

set(APEIRON_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../apeiron")
set(APEIRON_LIBRARY_DIRECTORY "${APEIRON_DIRECTORY}/external")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}
    ${APEIRON_DIRECTORY}
    ${APEIRON_LIBRARY_DIRECTORY}
    ${APEIRON_LIBRARY_DIRECTORY}/SDL2/x86_64-w64-mingw32/include
    ${APEIRON_LIBRARY_DIRECTORY}/glew/include
    ${APEIRON_LIBRARY_DIRECTORY}/glm)

link_directories(${APEIRON_LIBRARY_DIRECTORY}/SDL2/x86_64-w64-mingw32/lib
    ${APEIRON_LIBRARY_DIRECTORY}/glew/lib/Release/x64)

add_executable(point_cloud
    ${APEIRON_DIRECTORY}/opengl/shader.cpp
    ${APEIRON_DIRECTORY}/opengl/shader.h
    ${APEIRON_DIRECTORY}/opengl/renderer.cpp
    ${APEIRON_DIRECTORY}/opengl/renderer.h
    ${APEIRON_DIRECTORY}/opengl/texture.cpp
    ${APEIRON_DIRECTORY}/opengl/texture.h
    ${APEIRON_DIRECTORY}/opengl/tileset.cpp
    ${APEIRON_DIRECTORY}/opengl/tileset.h
    ${APEIRON_DIRECTORY}/opengl/shape.cpp
    ${APEIRON_DIRECTORY}/opengl/shape.h
    ${APEIRON_DIRECTORY}/opengl/points.cpp
    ${APEIRON_DIRECTORY}/opengl/points.h
    ${APEIRON_DIRECTORY}/opengl/grid.cpp
    ${APEIRON_DIRECTORY}/opengl/grid.h
    ${APEIRON_DIRECTORY}/engine/error.h
    ${APEIRON_DIRECTORY}/engine/input.h
    ${APEIRON_DIRECTORY}/engine/entity.h
    ${APEIRON_DIRECTORY}/engine/image_loader.cpp
    ${APEIRON_DIRECTORY}/engine/image_loader.h
    ${APEIRON_DIRECTORY}/engine/camera.cpp
    ${APEIRON_DIRECTORY}/engine/camera.h
    ${APEIRON_DIRECTORY}/prefab/ground.h
    source/string_utils.h
    source/main.cpp
    source/point_cloud.cpp
    source/point_cloud.h
    source/world.cpp
    source/world.h)

target_link_libraries(point_cloud -lmingw32 -lglew32 -lglu32 -lopengl32 -lSDL2main -lSDL2)
