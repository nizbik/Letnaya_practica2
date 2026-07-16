# CMakeLists.txt - тесты
# Зубехин Никита
# МК-101

get_all_sources(${CMAKE_CURRENT_SOURCE_DIR} TEST_SOURCES)

add_executable(test_hex ${TEST_SOURCES})


target_link_libraries(test_hex PRIVATE hex_lib)


add_test(NAME HexLogicTests COMMAND test_hex)