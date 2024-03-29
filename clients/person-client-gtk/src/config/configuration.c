#include "configuration.h"
#include <string.h>
#include <ini.h>

#define MATCH(s, n) strcmp(section, s) == 0 && strcmp(name, n) == 0

static int handler (void* user, const char* section, const char* name, const char* value);

bool configuration_init (configuration_t *conf)
{
    bool status = false;

    if (conf != NULL)
    {
        memset (conf, 0, sizeof (configuration_t));
        status = true;
    }

    return status;
}

bool configuration_load (configuration_t *conf)
{
    bool status = true;

    if (conf == NULL || ini_parse (CONFIGURATION_FILE_PATH, handler, conf) < 0)
    {        
        status = false;
    }

    return status;
}

static int handler (void* user, const char* section, const char* name, const char* value)
{
    configuration_t* config = (configuration_t*)user;
   
    if (MATCH(CONFIGURATION_SECTOR_SERVER, CONFIGURATION_SECTOR_VALUE_ADDRESS))
    {
        strncpy (config->address, value, CONFIGURATION_ADDRESS_MAX_LEN);
    }
    else if (MATCH(CONFIGURATION_SECTOR_SERVER, CONFIGURATION_SECTOR_VALUE_PORT))
    {
        strncpy (config->port, value, CONFIGURATION_PORT_MAX_LEN);
    }
    else if (MATCH(CONFIGURATION_SECTOR_SERVER, CONFIGURATION_SECTOR_VALUE_ENDPOINT))
    {
        strncpy (config->endpoint, value, CONFIGURATION_ENDPOINT_MAX_LEN);
    }
    else
    {
        return 0;  /* unknown section/name, error */
    }
    return 1;
}