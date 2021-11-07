#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <person.h>
#include <use_cases.h>

void use_case_person_add_new(repository_base *repository)
{
    store_action_t store;
    person_t person;

    person = person_create();

    store.action = repo_insert;
    store.id = -1;
    store.amount = 1;
    store.person = &person;

    repository->store(repository->object, &store);
}