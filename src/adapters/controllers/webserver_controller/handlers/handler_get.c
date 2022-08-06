#include "handlers.h"
#include <string.h>
#include <stdlib.h>

static cJSON *handler_get_all (void *object);

int handler_get (struct mg_connection *conn, void *data)
{
    int status = http_ok;
    cJSON *json;

    json = handler_get_all (data);

    if (json == NULL)
    {
        json = serialize_error ("No Content", "There is no registries");
        status = http_no_content;
    }

    send_json (conn, json, status);
    cJSON_Delete (json);

    return status;
}

static cJSON *handler_get_all (void *object)
{
    cJSON *json;

    person_controller_webserver_t *controller =  (person_controller_webserver_t *)object;

    person_t *list = NULL;
    unsigned int amount = 0;

    controller->service->base.getall (controller->service->base.object, &list, &amount);

    json = serialize_person_list (list, amount);

    free (list);

    return json;
}