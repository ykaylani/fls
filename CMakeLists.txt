cmake_minimum_required(VERSION 4.0)
project(fls LANGUAGES CXX CUDA)

set(CMAKE_CUDA_STANDARD 26)

add_executable(fls src/tempo/sl.cu include/internal/sdatal.h include/front/vinterface.h src/tempo/siminstance.h)
set_target_properties(fls PROPERTIES CUDA_SEPARABLE_COMPILATION ON)
