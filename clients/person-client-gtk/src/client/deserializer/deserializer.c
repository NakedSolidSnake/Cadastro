#include "deserializer.h"

static unsigned int deserializer_list_get_size (cJSON *list);
bool deserialize_person_list (person_list_t *person_list, const char *buffer)
{
    unsigned int count = 0;
    bool status = false;
    cJSON *person = NULL;
    cJSON *persons = NULL;
    cJSON *json = cJSON_Parse (buffer);

    if (json != NULL)
    {
        persons = cJSON_GetObjectItemCaseSensitive (json, "persons");
        
        count = deserializer_list_get_size (persons);

        person_list->array = array_list_create (count , sizeof (person_t));

        cJSON_ArrayForEach (person, persons)
        {
            person_t p = deserializer_person (person);
            array_list_insert (person_list->array, &p);
            status = true;
        }

        cJSON_Delete (json);
    }

    return status;
}

person_t deserializer_person (cJSON *json)
{
    cJSON *id = cJSON_GetObjectItem (json, "id");
    cJSON *name = cJSON_GetObjectItemCaseSensitive (json, "name");
    cJSON *address = cJSON_GetObjectItemCaseSensitive (json, "address");
    cJSON *age = cJSON_GetObjectItem (json, "age");

    person_t person = person_create_id (id->valueint, name->valuestring, address->valuestring, age->valueint);

    return person;
}

static unsigned int deserializer_list_get_size (cJSON *list)
{
    unsigned int amount = 0;
    cJSON *item;

    cJSON_ArrayForEach (item, list)
    {
        amount ++;
    }

    return amount;
}