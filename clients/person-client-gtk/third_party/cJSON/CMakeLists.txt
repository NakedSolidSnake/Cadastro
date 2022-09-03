add_library(cJSON "")
target_sources (cJSON
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/cJSON.c
    ${CMAKE_CURRENT_LIST_DIR}/cJSON_Utils.c
)
target_include_directories (cJSON
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)