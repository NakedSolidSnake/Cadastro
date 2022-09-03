add_library(ini "")
target_sources (ini
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/ini.c
)
target_include_directories (ini
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)