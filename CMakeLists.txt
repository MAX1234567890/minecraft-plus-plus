cmake_minimum_required(VERSION 3.10)
project(GLMC CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_MODULE_PATH /usr/local/lib/cmake)
set(CMAKE_PREFIX_PATH /usr/local/lib/cmake/glfw3)

set(CMAKE_CXX_COMPILER clang++)

find_package(PkgConfig REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

include_directories(/usr/local/include glad)
include_directories(${GLFW_INCLUDE_DIRS})
link_libraries(m)
link_libraries(dl)

#find_library(COCOA_LIBRARY Cocoa REQUIRED)
#find_library(IOKIT_LIBRARY IOKit REQUIRED)
#find_library(COREVID_LIBRARY CoreVideo REQUIRED)

set(CMAKE_CXX_STANDARD 17)

add_executable(GLMC main.cpp glad.cpp linmath.h window.cpp window.h shader.cpp shader.h mesh.cpp mesh.h gl.h input.cpp input.h stb_image.h texture.cpp texture.h gl.cpp block.h chunk.h chunk.cpp chunk_mesher.cpp chunk_mesher.h world.cpp world.h camera.cpp camera.h config.h perlin.h perlin.cpp physics.cpp physics.h block.cpp entity.cpp entity.h utils.cpp utils.h raycast.cpp raycast.h lights.cpp lights.h)
target_link_libraries(GLMC
        ${OPENGL_LIBRARIES}
        #        ${COCOA_LIBRARY}
        #        ${COREVID_LIBRARY}
        #        ${IOKIT_LIBRARY}
        ${GLFW3_LIBRARY}
        glfw)

add_compile_options(-lm -pthread)
add_link_options(-lm -pthread)