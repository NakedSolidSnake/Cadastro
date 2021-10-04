#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <person.h>
#include <use_cases.h>

void use_case_person_delete(repository_base *repository)
{
    int items = 0;
    person_t *person_list;
    repository->recover_list(repository->object, &person_list, &items);

    char *name_delete = person_input_name();

    for(int i = 0; i < items; i++)
    {
        if(strncmp(name_delete, person_list[i].name, PERSON_NAME_LEN) == 0)
        {
            memset(&person_list[i], 0, sizeof(person_t));
            break;
        }
    }

    repository->store_list(repository->object, person_list, items);

    free(name_delete);
    free(person_list);
}