#include "serializer.h"
#include <cJSON.h>

char *serialize_person (person_t *person)
{
    cJSON *person_json = NULL;
    cJSON *name = NULL;
    cJSON *address = NULL;
    cJSON *age = NULL;
    char *json_string = NULL;

    person_json = cJSON_CreateObject ();

    if (person_json != NULL)
    {
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

        json_string = cJSON_PrintUnformatted (person_json);
        cJSON_Delete (person_json);
    }

    return json_string;
}