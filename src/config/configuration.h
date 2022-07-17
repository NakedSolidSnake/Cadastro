#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

#include <stdbool.h>

#define CONFIGURATION_REPOSITORY_TYPE_FILE      "file"
#define CONFIGURATION_REPOSITORY_TYPE_SQLITE    "sqlite"

#define CONFIGURATION_CONTROLLER_TYPE_CLI       "cli"
#define CONFIGURATION_CONTROLLER_TYPE_GTK       "gtk"

#define CONFIGURATION_REPOSITORY_MAX_LEN        50
#define CONFIGURATION_CONTROLLER_MAX_LEN        50

#define CONFIGURATION_FILE_PATH                 "config/config.ini"

typedef struct 
{
    char repository_type[CONFIGURATION_REPOSITORY_MAX_LEN];
    char controller_type[CONFIGURATION_CONTROLLER_MAX_LEN];
} configuration_t;

bool configuration_init (configuration_t *conf);
bool configuration_load (configuration_t *conf);

#endif /* CONFIGURATION_H_ */
