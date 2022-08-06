#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

#include <stdbool.h>

#define CONFIGURATION_SECTOR_CONTROLLER         "controller"
#define CONFIGURATION_SECTOR_REPOSITORY         "repository"
#define CONFIGURATION_SECTOR_WEBSERVER           "server"

#define CONFIGURATION_SECTOR_VALUE_TYPE         "type"
#define CONFIGURATION_SECTOR_VALUE_PORT         "port"

#define CONFIGURATION_REPOSITORY_TYPE_FILE      "file"
#define CONFIGURATION_REPOSITORY_TYPE_SQLITE    "sqlite"

#define CONFIGURATION_CONTROLLER_TYPE_CLI       "cli"
#define CONFIGURATION_CONTROLLER_TYPE_GTK       "gtk"
#define CONFIGURATION_CONTROLLER_TYPE_WEBSERVER "webserver"

#define CONFIGURATION_REPOSITORY_MAX_LEN        50
#define CONFIGURATION_CONTROLLER_MAX_LEN        50
#define CONFIGURATION_WEBSERVER_MAX_LEN         10

#define CONFIGURATION_FILE_PATH                 "config/config.ini"

typedef struct 
{
    char repository_type[CONFIGURATION_REPOSITORY_MAX_LEN];
    char controller_type[CONFIGURATION_CONTROLLER_MAX_LEN];
    struct 
    {
        char port [CONFIGURATION_WEBSERVER_MAX_LEN];
    } webserver;
} configuration_t;

bool configuration_init (configuration_t *conf);
bool configuration_load (configuration_t *conf);

#endif /* CONFIGURATION_H_ */
