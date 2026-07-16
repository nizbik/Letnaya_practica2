# CMakeLists.txt - настройки сборки библиотеки.
#Зубехин Никита
# МК-101

get_all_sources(${CMAKE_CURRENT_SOURCE_DIR} LIB_SOURCES)


add_library(hex_lib ${LIB_SOURCES})


target_include_directories(hex_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})