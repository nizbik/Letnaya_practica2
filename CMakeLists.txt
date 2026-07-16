# CMakeLists.txt - корневой файл сборки проекта.
# Зубехин Никита
# МК-101


cmake_minimum_required(VERSION 3.10)


project(letnaya_practica_2 C)


set(CMAKE_C_STANDARD 11)


include(${CMAKE_SOURCE_DIR}/cmake/MyFunctions.cmake)


enable_testing()


add_subdirectory(lib)
add_subdirectory(app)
add_subdirectory(tests)