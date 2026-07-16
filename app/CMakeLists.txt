# CMakeLists.txt - настройки сборки основной программы.
# Зубехин Никита
# МК-101

get_all_sources(${CMAKE_CURRENT_SOURCE_DIR} SRC_SOURCES)


add_executable(prog ${SRC_SOURCES})


target_link_libraries(prog PRIVATE hex_lib)
