#include "handlers.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

static cJSON *handler_update (void *object, char *buffer, int size, int id);

int handler_put (struct mg_connection *conn, void *data)
{
    int status = http_bad_request;
    cJSON *json;
    char buffer [1024] = {0};
    char param [128] = {0};
    int size;

    const struct mg_request_info *ri = mg_get_request_info (conn);

    if (ri->query_string != NULL)
    {
        mg_get_var (ri->query_string, strlen (ri->query_string), "id", param, 128);
        if (strlen (param) > 0)
        {
            size = mg_read (conn, buffer, sizeof (buffer) - 1);
            buffer[size] = 0;

            json = handler_update (data, buffer, size, atoi (param));

            if (json != NULL)
                status = http_ok;
            else
            {
                json = serialize_error ("No Content", "There is no registries");
                status = http_not_found;
            }
        }

        else 
            json = serialize_error ("Bad Request", "/persons?id<number>");
    }

    else 
        json = serialize_error ("Bad Request", "/persons?id<number>");
    
    send_json (conn, json, status);
    cJSON_Delete (json);

    return status;
}

static cJSON *handler_update (void *object, char *buffer, int size, int id)
{
    person_t person;
    cJSON *json;
    person_controller_webserver_t *controller =  (person_controller_webserver_t *)object;

    if (deserialize_person (buffer, &person) == true)
    {
        person.id = id;

        if (controller->service->base.update (controller->service->base.object, &person) == true)
        {
            json = serialize_error ("Accepted", "Registry Updated");
        }
    }

    return json;
}
