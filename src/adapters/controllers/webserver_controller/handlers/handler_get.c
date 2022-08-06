#include "handlers.h"
#include <string.h>
#include <stdlib.h>

static cJSON *handler_get_all (void *object);
static cJSON *handler_find (void *object, const char *name);

int handler_get (struct mg_connection *conn, void *data)
{
    int status = http_ok;
    cJSON *json;
    char buffer [1024];

    const struct mg_request_info *ri = mg_get_request_info (conn);

    if (ri->query_string != NULL)
    {
        mg_get_var (ri->query_string, strlen (ri->query_string), "name", buffer, 1024);
        json = handler_find (data, buffer);
    }
    else 
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

static cJSON *handler_find (void *object, const char *name)
{
    cJSON *json;

    person_controller_webserver_t *controller =  (person_controller_webserver_t *)object;

    person_t person = person_create (name, NULL, 0);

    if (strlen (name) > 0 && 
        controller->service->base.find (controller->service->base.object, &person) == true)
    {
        json = serialize_person (NULL, &person);
    }

    return json;
}