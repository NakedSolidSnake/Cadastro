#include "deserializer.h"
#include <cJSON.h>

bool deserialize_person_list (person_list_t *person_list, const char *buffer)
{
    int count = 0;
    bool status = false;
    cJSON *person = NULL;
    cJSON *persons = NULL;
    cJSON *json = cJSON_Parse (buffer);

    if (json != NULL)
    {
        persons = cJSON_GetObjectItemCaseSensitive (json, "persons");
        cJSON_ArrayForEach (person, persons)
        {
            count ++;
        }

        person_list->array = array_list_create (count , sizeof (person_t));
        cJSON_ArrayForEach (person, persons)
        {
            cJSON *id = cJSON_GetObjectItem (person, "id");
            cJSON *name = cJSON_GetObjectItemCaseSensitive (person, "name");
            cJSON *address = cJSON_GetObjectItemCaseSensitive (person, "address");
            cJSON *age = cJSON_GetObjectItem (person, "age");

            status = true;

            person_t p = person_create_id (id->valueint, name->valuestring, address->valuestring, age->valueint);
            array_list_insert (person_list->array, &p);
        }

        cJSON_Delete (json);
    }

    return status;
}