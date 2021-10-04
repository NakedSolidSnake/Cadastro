#include <stdio.h>
#include <stdlib.h>
#include <use_cases.h>

void use_case_person_list(repository_base *repository)
{
    person_t *person_list;
    int items;

    repository-> recover_list(repository->object, &person_list, &items);

    for(int i = 0; i < items; i++)
    {
        printf("%d: %s %s %d\n", i + 1, person_list[i].name, person_list[i].address, person_list[i].age);
    }

    free(person_list);
}