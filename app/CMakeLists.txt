# CMakeLists.txt - настройки сборки основной программы.
# Зубехин Никита
# МК-101


get_all_sources(${CMAKE_CURRENT_SOURCE_DIR}/src APP_SOURCES)


add_executable(letnaya_practica_2 ${APP_SOURCES})


target_include_directories(letnaya_practica_2 PRIVATE ${CMAKE_SOURCE_DIR}/lib/include)


target_link_libraries(letnaya_practica_2 PRIVATE hex_core_lib)