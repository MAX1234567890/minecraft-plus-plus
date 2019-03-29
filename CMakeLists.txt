cmake_minimum_required(VERSION 3.10)
project(GLMC CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_MODULE_PATH /usr/local/lib/cmake)
set(CMAKE_PREFIX_PATH /usr/local/lib/cmake/glfw3)

set(CMAKE_C_COMPILER gcc)

find_package (PkgConfig REQUIRED)
find_package (OpenGL REQUIRED)
find_package (glfw3 REQUIRED)

include_directories(/usr/local/include glad)
include_directories(${GLFW_INCLUDE_DIRS})
link_libraries(m)
link_libraries(dl)

#find_library(COCOA_LIBRARY Cocoa REQUIRED)
#find_library(IOKIT_LIBRARY IOKit REQUIRED)
#find_library(COREVID_LIBRARY CoreVideo REQUIRED)

set(CMAKE_C_STANDARD 99)

add_executable(GLMC main.c glad.c linmath.h window.c window.h shader.cpp shader.h mesh.c mesh.h gl.h input.c input.h stb_image.h texture.c texture.h gl.c block.h chunk.h chunk.c chunk_mesher.c chunk_mesher.h world.c world.h camera.c camera.h config.h perlin.h perlin.c physics.c physics.h block.c entity.c entity.h utils.c utils.h raycast.c raycast.h lights.c lights.h)
target_link_libraries (GLMC
        ${OPENGL_LIBRARIES}
#        ${COCOA_LIBRARY}
#        ${COREVID_LIBRARY}
#        ${IOKIT_LIBRARY}
        ${GLFW3_LIBRARY}
        glfw)

add_compile_options(-lm -pthread)
add_link_options(-lm -pthread)