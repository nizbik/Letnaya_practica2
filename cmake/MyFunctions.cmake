# MyFunctions.cmake - вспомогательные функции для CMake.
# Зубехин Никита
# МК-101

function(get_all_sources dir result_var)
    file(GLOB SOURCE_FILES CONFIGURE_DEPENDS
        "${dir}/*.c"
        "${dir}/*.h"
    )
    set(${result_var} ${SOURCE_FILES} PARENT_SCOPE)
endfunction()


function(set_strict_warnings target_name)
    target_compile_options(${target_name} PRIVATE 
        -Wall -Wextra -Wpedantic -Werror
    )
endfunction()