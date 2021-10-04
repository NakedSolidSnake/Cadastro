#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <person.h>
#include <use_cases.h>

void use_case_person_update(repository_base *repository)
{
    int id = -1;

    int items = 0;
    person_t *person_list;

    repository->recover_list(repository->object, &person_list, &items);

    char *name_update = person_input_name();

    for (int i = 0; i < items; i++)
    {
        if(strncmp(name_update, person_list[i].name, PERSON_NAME_LEN) == 0)
        {
            id = i;
            break;
        }
    }
    
    if(id != -1)
    {
        memset(&person_list[id], 0, sizeof(person_t));
        person_list[id] = person_create();
    }

    repository->store_list(repository->object, person_list, items);

    free(name_update);
    free(person_list);
}