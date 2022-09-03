#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

#include <stdbool.h>

#define CONFIGURATION_SECTOR_SERVER             "server"

#define CONFIGURATION_SECTOR_VALUE_ADDRESS      "address"
#define CONFIGURATION_SECTOR_VALUE_PORT         "port"
#define CONFIGURATION_SECTOR_VALUE_ENDPOINT     "endpoint"

#define CONFIGURATION_ADDRESS_MAX_LEN           200
#define CONFIGURATION_PORT_MAX_LEN              10
#define CONFIGURATION_ENDPOINT_MAX_LEN          50

#define CONFIGURATION_FILE_PATH                 "config/config.ini"

typedef struct 
{
    char address [CONFIGURATION_ADDRESS_MAX_LEN];
    char port [CONFIGURATION_PORT_MAX_LEN];
    char endpoint [CONFIGURATION_ENDPOINT_MAX_LEN];
} configuration_t;

bool configuration_init (configuration_t *conf);
bool configuration_load (configuration_t *conf);

#endif /* CONFIGURATION_H_ */
