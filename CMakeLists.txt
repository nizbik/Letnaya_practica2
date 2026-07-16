# CMakeLists.txt - корневой файл сборки проекта.
# Зубехин Никита
# МК-101

include(MyFunctions.cmake)
cmake_minimum_required(VERSION 3.10)
project(letnaya_practica_2)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

enable_testing()


add_subdirectory(lib)
add_subdirectory(src)
add_subdirectory(tests)