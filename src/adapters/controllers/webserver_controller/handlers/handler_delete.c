#include "handlers.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

static cJSON *handler_remove (void *object, int id);

int handler_delete (struct mg_connection *conn, void *data)
{
    int status = http_ok;
    cJSON *json;
    char buffer [1024] = {0};

    const struct mg_request_info *ri = mg_get_request_info (conn);

    if (ri->query_string != NULL)
    {
        mg_get_var (ri->query_string, strlen (ri->query_string), "id", buffer, 1024);
        json = handler_remove (data, atoi (buffer));

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
    
    send_json (conn, json, status);
    cJSON_Delete (json);

    return status;
}

static cJSON *handler_remove (void *object, int id)
{
    cJSON *json;

    person_controller_webserver_t *controller =  (person_controller_webserver_t *)object;

    person_t person = {.id = id, .age = -1};

    if (controller->service->base.remove (controller->service->base.object, &person) == true)
    {
        json = serialize_person (NULL, &person);
    }

    return json;
}
