#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <person.h>
#include <use_cases.h>

void use_case_person_delete(repository_base *repository)
{
    int items = 0;
    person_t *person_list;
    store_action_t store;
    repository->recover_list(repository->object, &person_list, &items);

    char *name_delete = person_input_name();

    for(int i = 0; i < items; i++)
    {
        if(strncmp(name_delete, person_list[i].name, PERSON_NAME_LEN) == 0)
        {
            memset(&person_list[i], 0, sizeof(person_t));
            store.id = i;
            store.action = repo_delete;
            store.amount = items;
            store.person = &person_list[i];
            repository->store(repository->object, &store);
            break;
        }
    }

    free(name_delete);
    free(person_list);
}