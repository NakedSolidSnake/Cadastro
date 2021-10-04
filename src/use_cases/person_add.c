#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <person.h>
#include <use_cases.h>

void use_case_person_add_new(repository_base *repository)
{
    person_t person;

    person = person_create();
    repository->store(repository->object, &person);
}