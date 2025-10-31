cmake_minimum_required(VERSION 4.0)
project(fls LANGUAGES CXX CUDA)

find_package(OpenGL REQUIRED)

set(CMAKE_CUDA_STANDARD 26)

if(WIN32)
    find_path(OPENGL_INCLUDE_DIR GL/gl.h)
    find_library(OPENGL_gl_LIBRARY opengl32)
    find_library(OPENGL_glu_LIBRARY glu32)

    add_executable(fls src/tempo/loop.cu)
    target_include_directories(fls PRIVATE ${OPENGL_INCLUDE_DIR})
    target_link_libraries(fls PRIVATE ${OPENGL_gl_LIBRARY} ${OPENGL_glu_LIBRARY})
else()
    # Linux/macOS can use the modern approach
    find_package(OpenGL REQUIRED)
    add_executable(fls src/tempo/loop.cu)
    target_link_libraries(fls PRIVATE OpenGL::OpenGL)
endif()

set_target_properties(fls PROPERTIES CUDA_SEPARABLE_COMPILATION ON)
target_compile_options(fls PRIVATE $<$<COMPILE_LANGUAGE:CUDA>:-use_fast_math>)