#include "handlers.h"
#include <string.h>
#include <stdlib.h>

int handler_requests (struct mg_connection *conn, void *data)
{
    const struct mg_request_info *ri = mg_get_request_info (conn);

    static handler_requests_map_t map = 
    {
        .requests = 
        {
            {.method = HANDLER_REQUEST_GET,    .handler = handler_get},
            {.method = HANDLER_REQUEST_POST,   .handler = handler_post},
            {.method = HANDLER_REQUEST_DELETE, .handler = handler_delete},
        },
        .amount = 3
    };

    for (unsigned char i = 0; i < map.amount; i++)
    {
        handler_request_map_t *rm = &map.requests[i];

        if (strcmp (ri->request_method, rm->method) == 0)
            return rm->handler (conn, data);
    }

    mg_send_http_error (conn, 405, "Only, GET, PUT, POST, DELETE are supported");
    return 405;
}





int send_json (struct mg_connection *conn, cJSON *json_obj, http_status_t status)
{
    char *json_string = cJSON_PrintUnformatted (json_obj);
    size_t json_str_len = strlen (json_string);
    char json_buffer [32] = {0};
    snprintf (json_buffer, 32, "%lu", json_str_len);

    mg_response_header_start (conn, status);
    mg_response_header_add (conn,
                            "Content-Type",
                            "application/json; charset=utf-8",
                            -1);
    mg_response_header_add (conn, "Content-Length", json_buffer, -1);

    mg_response_header_send (conn);

    mg_write (conn, json_string, json_str_len);

    cJSON_free (json_string);

    return (int) json_str_len;
}

cJSON *serialize_person_list (person_t *list, unsigned int amount)
{
    cJSON *obj = cJSON_CreateObject ();
    cJSON *array = NULL;

    if (obj != NULL) 
    {
        array = cJSON_AddArrayToObject (obj, "persons");
        if (array != NULL)
        {
            for (unsigned int i = 0; i < amount; i++)
                serialize_person (array, &list[i]);
        }
    }

    return obj;
}

cJSON *serialize_person (cJSON *obj, person_t *person)
{
    cJSON *person_json = NULL;
    cJSON *name = NULL;
    cJSON *address = NULL;
    cJSON *age = NULL;
    cJSON *id = NULL;

    person_json = cJSON_CreateObject ();

    if (person_json != NULL)
    {
        id = cJSON_CreateNumber (person->id);
        cJSON_AddItemToObject (person_json, "id", id);

        if (person->name != NULL && strlen (person->name) > 0)
        {
            name = cJSON_CreateString (person->name);
            cJSON_AddItemToObject (person_json, "name", name);
        }

        if (person->address != NULL && strlen (person->address) > 0)
        {
            address = cJSON_CreateString (person->address);
            cJSON_AddItemToObject (person_json, "address", address);
        }

        if (person->age >= 0)
        {
            age = cJSON_CreateNumber (person->age);
            cJSON_AddItemToObject (person_json, "age", age);
        }

        if (obj != NULL)
            cJSON_AddItemToArray (obj, person_json);
    }

    return person_json;
}

cJSON *serialize_error (const char *error, const char *hint)
{
    cJSON *json = cJSON_CreateObject ();

    if (json != NULL)
    {
        cJSON_AddStringToObject (json, "error", error);
        cJSON_AddStringToObject (json, "hint", hint);
    }

    return json;    
}

bool deserialize_person (const char *buffer, person_t *person)
{
    cJSON *name;
    cJSON *address;
    cJSON *age;
    cJSON *json;
    
    person_t person_temp;
    bool status = false;

    cJSON *person_json = cJSON_Parse (buffer);
    if (person_json != NULL)
    {
        json = cJSON_CreateObject ();
        if (json != NULL)
        {
            name = cJSON_GetObjectItemCaseSensitive (person_json, "name");
            address = cJSON_GetObjectItemCaseSensitive (person_json, "address");
            age = cJSON_GetObjectItem (person_json, "age");

            person_temp = person_create (name->valuestring, address->valuestring, (int)age->valuedouble);

            memcpy (person, &person_temp, sizeof (person_t));

            cJSON_Delete (json);
            status = true;
        }

        cJSON_Delete (person_json);
    }

    return status;
}