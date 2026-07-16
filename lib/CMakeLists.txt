# CMakeLists.txt - настройки сборки библиотеки.
# Зубехин Никита
# МК-101


# CMakeLists.txt - настройки сборки библиотеки.
# Зубехин Никита
# МК-101

get_all_sources(${CMAKE_CURRENT_SOURCE_DIR}/src LIB_SOURCES)


file(GLOB INCLUDE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")


add_library(hex_core_lib ${LIB_SOURCES} ${INCLUDE_FILES})


target_include_directories(hex_core_lib PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)