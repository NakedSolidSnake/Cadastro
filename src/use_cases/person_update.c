#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <person.h>
#include <use_cases.h>

void use_case_person_update(repository_base *repository)
{
    int id = -1;
    store_action_t store;
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
        person_t person_tmp;
        store.person = person_list;
        store.id = id;
        store.action = repo_update;
        store.amount = items;
        // memset(&person_list[id], 0, sizeof(person_t));
        person_tmp = person_create();
        strncpy(person_list[id].name, person_tmp.name, PERSON_NAME_LEN);
        strncpy(person_list[id].address, person_tmp.address, PERSON_ADDRESS_LEN);
        person_list[id].age = person_tmp.age;

        repository->store(repository->object, &store);
    }


    free(name_update);
    free(person_list);
}