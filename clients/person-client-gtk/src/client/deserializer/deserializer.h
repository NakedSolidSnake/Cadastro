#ifndef DESERIALIZER_H_
#define DESERIALIZER_H_

#include <stdbool.h>
#include <person.h>
#include <array_list.h>
#include <cJSON.h>

typedef struct 
{
    array_list_t *array;
} person_list_t;

bool deserialize_person_list (person_list_t *person_list, const char *buffer);
person_t deserializer_person (cJSON *json);

#endif /* DESERIALIZER_H_ */
