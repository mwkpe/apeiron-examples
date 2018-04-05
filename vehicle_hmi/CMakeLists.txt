cmake_minimum_required(VERSION 3.10)
project(vehicle_hmi)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-O3 -Wall -Wextra -pedantic-errors")

set(APEIRON_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../apeiron")
set(LIBRARY_DIRECTORY "${APEIRON_DIRECTORY}/external")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}
    ${APEIRON_DIRECTORY}
    ${LIBRARY_DIRECTORY}
    ${LIBRARY_DIRECTORY}/SDL2/x86_64-w64-mingw32/include
    ${LIBRARY_DIRECTORY}/glew/include
    ${LIBRARY_DIRECTORY}/glm)

link_directories(${LIBRARY_DIRECTORY}/SDL2/x86_64-w64-mingw32/lib
    ${LIBRARY_DIRECTORY}/glew/lib/Release/x64)

add_executable(vehicle_hmi
    ${LIBRARY_DIRECTORY}/imgui/imgui.cpp
    ${LIBRARY_DIRECTORY}/imgui/imgui.h
    ${LIBRARY_DIRECTORY}/imgui/imgui_draw.cpp
    ${LIBRARY_DIRECTORY}/imgui/imgui_internal.h
    ${LIBRARY_DIRECTORY}/imgui/examples/sdl_opengl3_example/imgui_impl_sdl_gl3.cpp
    ${LIBRARY_DIRECTORY}/imgui/examples/sdl_opengl3_example/imgui_impl_sdl_gl3.h
    ${APEIRON_DIRECTORY}/opengl/shader.cpp
    ${APEIRON_DIRECTORY}/opengl/shader.h
    ${APEIRON_DIRECTORY}/opengl/renderer.cpp
    ${APEIRON_DIRECTORY}/opengl/renderer.h
    ${APEIRON_DIRECTORY}/opengl/shape.cpp
    ${APEIRON_DIRECTORY}/opengl/shape.h
    ${APEIRON_DIRECTORY}/opengl/texture.cpp
    ${APEIRON_DIRECTORY}/opengl/texture.h
    ${APEIRON_DIRECTORY}/opengl/grid.cpp
    ${APEIRON_DIRECTORY}/opengl/grid.h
    ${APEIRON_DIRECTORY}/opengl/line_array.cpp
    ${APEIRON_DIRECTORY}/opengl/line_array.h
    ${APEIRON_DIRECTORY}/opengl/rectangle.cpp
    ${APEIRON_DIRECTORY}/opengl/rectangle.h
    ${APEIRON_DIRECTORY}/opengl/cuboid.cpp
    ${APEIRON_DIRECTORY}/opengl/cuboid.h
    ${APEIRON_DIRECTORY}/opengl/cylinder.cpp
    ${APEIRON_DIRECTORY}/opengl/cylinder.h
    ${APEIRON_DIRECTORY}/opengl/model.cpp
    ${APEIRON_DIRECTORY}/opengl/model.h
    ${APEIRON_DIRECTORY}/opengl/gui.cpp
    ${APEIRON_DIRECTORY}/opengl/gui.h
    ${APEIRON_DIRECTORY}/engine/error.h
    ${APEIRON_DIRECTORY}/engine/input.h
    ${APEIRON_DIRECTORY}/engine/entity.h
    ${APEIRON_DIRECTORY}/engine/camera.cpp
    ${APEIRON_DIRECTORY}/engine/camera.h
    ${APEIRON_DIRECTORY}/engine/image_loader.cpp
    ${APEIRON_DIRECTORY}/engine/image_loader.h
    ${APEIRON_DIRECTORY}/engine/model_loader.cpp
    ${APEIRON_DIRECTORY}/engine/model_loader.h
    ${APEIRON_DIRECTORY}/engine/model_flags.h
    main.cpp
    options.cpp
    options.h
    menu.h
    menu.cpp
    world.cpp
    world.h
    vehicle.cpp
    vehicle.h
    light.h
    ground.h
    position_marker.cpp
    position_marker.h
    deviation_meter.cpp
    deviation_meter.h)

target_link_libraries(vehicle_hmi -lmingw32 -lglew32 -lglu32 -lopengl32 -lSDL2main -lSDL2)
