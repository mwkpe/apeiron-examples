cmake_minimum_required(VERSION 3.10)
project(vehicle_scene)

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

add_executable(vehicle_scene
    ${APEIRON_LIBRARY_DIRECTORY}/imgui/imgui.cpp
    ${APEIRON_LIBRARY_DIRECTORY}/imgui/imgui.h
    ${APEIRON_LIBRARY_DIRECTORY}/imgui/imgui_draw.cpp
    ${APEIRON_LIBRARY_DIRECTORY}/imgui/imgui_internal.h
    ${APEIRON_LIBRARY_DIRECTORY}/imgui/imgui_impl_sdl_gl3.cpp
    ${APEIRON_LIBRARY_DIRECTORY}/imgui/imgui_impl_sdl_gl3.h
    ${APEIRON_DIRECTORY}/opengl/shader.cpp
    ${APEIRON_DIRECTORY}/opengl/shader.h
    ${APEIRON_DIRECTORY}/opengl/renderer.cpp
    ${APEIRON_DIRECTORY}/opengl/renderer.h
    ${APEIRON_DIRECTORY}/opengl/shape.cpp
    ${APEIRON_DIRECTORY}/opengl/shape.h
    ${APEIRON_DIRECTORY}/opengl/texture.cpp
    ${APEIRON_DIRECTORY}/opengl/texture.h
    ${APEIRON_DIRECTORY}/opengl/tileset.cpp
    ${APEIRON_DIRECTORY}/opengl/tileset.h
    ${APEIRON_DIRECTORY}/opengl/grid.cpp
    ${APEIRON_DIRECTORY}/opengl/grid.h
    ${APEIRON_DIRECTORY}/opengl/triangles.cpp
    ${APEIRON_DIRECTORY}/opengl/triangles.h
    ${APEIRON_DIRECTORY}/opengl/rectangle.cpp
    ${APEIRON_DIRECTORY}/opengl/rectangle.h
    ${APEIRON_DIRECTORY}/opengl/cuboid.cpp
    ${APEIRON_DIRECTORY}/opengl/cuboid.h
    ${APEIRON_DIRECTORY}/opengl/model.cpp
    ${APEIRON_DIRECTORY}/opengl/model.h
    ${APEIRON_DIRECTORY}/opengl/gui.cpp
    ${APEIRON_DIRECTORY}/opengl/gui.h
    ${APEIRON_DIRECTORY}/engine/error.h
    ${APEIRON_DIRECTORY}/engine/input.h
    ${APEIRON_DIRECTORY}/engine/vertex.h
    ${APEIRON_DIRECTORY}/engine/entity.h
    ${APEIRON_DIRECTORY}/engine/camera.cpp
    ${APEIRON_DIRECTORY}/engine/camera.h
    ${APEIRON_DIRECTORY}/engine/text.h
    ${APEIRON_DIRECTORY}/engine/image_loader.cpp
    ${APEIRON_DIRECTORY}/engine/image_loader.h
    ${APEIRON_DIRECTORY}/engine/model_loader.cpp
    ${APEIRON_DIRECTORY}/engine/model_loader.h
    ${APEIRON_DIRECTORY}/engine/model_flags.h
    ${APEIRON_DIRECTORY}/prefab/light.h
    ${APEIRON_DIRECTORY}/prefab/ground.h
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

target_link_libraries(vehicle_scene -lmingw32 -lglew32 -lglu32 -lopengl32 -lSDL2main -lSDL2)
