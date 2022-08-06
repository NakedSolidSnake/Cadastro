cmake_minimum_required(VERSION 3.7.0)

project(Cadastro)

set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 1)
set(PROJECT_VERSION_PATCH 0)

set(CMAKE_C_FLAGS "-D_GNU_SOURCE -Wall -std=c99")
set (CMAKE_EXE_LINKER_FLAGS "-rdynamic")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_BUILD_TYPE Debug)

add_subdirectory(third_party)

find_package (PkgConfig)
if (PKG_CONFIG_FOUND)
    pkg_check_modules (GTK "gtk+-3.0")
    if (GTK_FOUND)
        add_executable(cadastro "")        
        target_sources(cadastro 
            PUBLIC 
            ${CMAKE_CURRENT_LIST_DIR}/src/main.c 
            ${CMAKE_CURRENT_LIST_DIR}/src/domain/model/person.c    
            ${CMAKE_CURRENT_LIST_DIR}/src/domain/services/person_service.c
            ${CMAKE_CURRENT_LIST_DIR}/src/adapters/repositories/person_repository_factory.c
            ${CMAKE_CURRENT_LIST_DIR}/src/adapters/repositories/file/person_repository_file.c
            ${CMAKE_CURRENT_LIST_DIR}/src/adapters/repositories/sqlite/person_repository_sqlite.c
            ${CMAKE_CURRENT_LIST_DIR}/src/adapters/controllers/person_controller_factory.c
            ${CMAKE_CURRENT_LIST_DIR}/src/adapters/controllers/cli_controller/person_controller_cli.c
            ${CMAKE_CURRENT_LIST_DIR}/src/adapters/controllers/cli_controller/cli/cli.c
            ${CMAKE_CURRENT_LIST_DIR}/src/adapters/controllers/gtk_controller/person_controller_gtk.c
            ${CMAKE_CURRENT_LIST_DIR}/src/adapters/controllers/gtk_controller/view/mainwindow/main_window.c
            ${CMAKE_CURRENT_LIST_DIR}/src/adapters/controllers/gtk_controller/view/insertdialog/insert_dialog.c
            ${CMAKE_CURRENT_LIST_DIR}/src/adapters/controllers/gtk_controller/view/editdialog/edit_dialog.c
            ${CMAKE_CURRENT_LIST_DIR}/src/config/configuration.c
            ${CMAKE_CURRENT_LIST_DIR}/src/adapters/controllers/webserver_controller/person_controller_webserver.c
            ${CMAKE_CURRENT_LIST_DIR}/src/adapters/controllers/webserver_controller/webserver/webserver.c
            ${CMAKE_CURRENT_LIST_DIR}/src/adapters/controllers/webserver_controller/handlers/handlers.c
            ${CMAKE_CURRENT_LIST_DIR}/src/adapters/controllers/webserver_controller/handlers/handler_get.c
            ${CMAKE_CURRENT_LIST_DIR}/src/adapters/controllers/webserver_controller/handlers/handler_post.c
            ${CMAKE_CURRENT_LIST_DIR}/src/adapters/controllers/webserver_controller/handlers/handler_delete.c
            ${CMAKE_CURRENT_LIST_DIR}/src/adapters/controllers/webserver_controller/handlers/handler_index.c
            ${CMAKE_CURRENT_LIST_DIR}/src/adapters/controllers/webserver_controller/handlers/handler_version.c
            
            )

        target_include_directories(cadastro 
            PUBLIC 
            ${CMAKE_CURRENT_LIST_DIR}/src/domain/model
            ${CMAKE_CURRENT_LIST_DIR}/src/domain/ports
            ${CMAKE_CURRENT_LIST_DIR}/src/domain/services
            ${CMAKE_CURRENT_LIST_DIR}/src/adapters/repositories
            ${CMAKE_CURRENT_LIST_DIR}/src/adapters/repositories/file 
            ${CMAKE_CURRENT_LIST_DIR}/src/adapters/repositories/sqlite
            ${CMAKE_CURRENT_LIST_DIR}/src/adapters/controllers
            ${CMAKE_CURRENT_LIST_DIR}/src/adapters/controllers/cli_controller
            ${CMAKE_CURRENT_LIST_DIR}/src/adapters/controllers/cli_controller/cli
            ${CMAKE_CURRENT_LIST_DIR}/src/adapters/controllers/gtk_controller
            ${CMAKE_CURRENT_LIST_DIR}/src/adapters/controllers/gtk_controller/view
            ${CMAKE_CURRENT_LIST_DIR}/src/adapters/controllers/gtk_controller/view/mainwindow
            ${CMAKE_CURRENT_LIST_DIR}/src/adapters/controllers/gtk_controller/view/insertdialog
            ${CMAKE_CURRENT_LIST_DIR}/src/adapters/controllers/gtk_controller/view/editdialog
            ${CMAKE_CURRENT_LIST_DIR}/src/adapters/controllers/webserver_controller
            ${CMAKE_CURRENT_LIST_DIR}/src/adapters/controllers/webserver_controller/handlers
            ${CMAKE_CURRENT_LIST_DIR}/src/adapters/controllers/webserver_controller/webserver
            ${CMAKE_CURRENT_LIST_DIR}/src/config
        )

        target_link_libraries(cadastro ${GTK_LIBRARIES} sqlite3 ini civetweb pthread dl cJSON)
        add_definitions( ${GTK_CFLAGS} ${GTK_CFLAGS_OTHER})
    endif ()
endif ()

add_custom_command(TARGET cadastro POST_BUILD 
                    COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_SOURCE_DIR}/resources 
                    ${CMAKE_BINARY_DIR}/bin/resources)   

add_custom_command(TARGET cadastro POST_BUILD 
                    COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_SOURCE_DIR}/config 
                    ${CMAKE_BINARY_DIR}/bin/config)

add_custom_command(TARGET cadastro POST_BUILD 
                    COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_SOURCE_DIR}/assets 
                    ${CMAKE_BINARY_DIR}/bin/assets) 