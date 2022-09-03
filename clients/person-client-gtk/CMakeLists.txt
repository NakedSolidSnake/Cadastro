cmake_minimum_required(VERSION 3.7.0)

project(Client)

set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 1)
set(PROJECT_VERSION_PATCH 0)

set(CMAKE_C_FLAGS "-D_GNU_SOURCE -Wall -std=c99")
set (CMAKE_EXE_LINKER_FLAGS "-rdynamic")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_BUILD_TYPE Debug)

add_subdirectory(third_party)
add_subdirectory(data_structures)

find_package (PkgConfig)
if (PKG_CONFIG_FOUND)
    pkg_check_modules (GTK "gtk+-3.0")
    if (GTK_FOUND)
        add_executable(client_gtk "")        
        target_sources(client_gtk 
            PUBLIC 
            ${CMAKE_CURRENT_LIST_DIR}/src/main.c 
            ${CMAKE_CURRENT_LIST_DIR}/src/client/domain/person.c    
            ${CMAKE_CURRENT_LIST_DIR}/src/client/person_client_gtk.c
            ${CMAKE_CURRENT_LIST_DIR}/src/client/view/mainwindow/main_window.c
            ${CMAKE_CURRENT_LIST_DIR}/src/client/view/insertdialog/insert_dialog.c
            ${CMAKE_CURRENT_LIST_DIR}/src/client/view/editdialog/edit_dialog.c
            ${CMAKE_CURRENT_LIST_DIR}/src/client/deserializer/deserializer.c
            ${CMAKE_CURRENT_LIST_DIR}/src/client/serializer/serializer.c
            
            )

        target_include_directories(client_gtk 
            PUBLIC 
            ${CMAKE_CURRENT_LIST_DIR}/src/client
            ${CMAKE_CURRENT_LIST_DIR}/src/client/domain
            ${CMAKE_CURRENT_LIST_DIR}/src/client/view
            ${CMAKE_CURRENT_LIST_DIR}/src/client/view/mainwindow
            ${CMAKE_CURRENT_LIST_DIR}/src/client/view/insertdialog
            ${CMAKE_CURRENT_LIST_DIR}/src/client/view/editdialog
            ${CMAKE_CURRENT_LIST_DIR}/src/client/deserializer
            ${CMAKE_CURRENT_LIST_DIR}/src/client/serializer
        )

        target_link_libraries(client_gtk ${GTK_LIBRARIES} curl cJSON structures_static)
        add_definitions( ${GTK_CFLAGS} ${GTK_CFLAGS_OTHER})
    endif ()
endif ()

add_custom_command(TARGET client_gtk POST_BUILD 
                    COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_SOURCE_DIR}/resources 
                    ${CMAKE_BINARY_DIR}/bin/resources)   
