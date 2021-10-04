#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <stdbool.h>
#include <person.h>

typedef struct 
{
    void *object;
    bool (*store)(void *object, const person_t *person);
    bool (*store_list)(void *object, const person_t *person_list, int items_amount);
    bool (*recover_list)(void *object, person_t **person_list, int *items_amount);
} repository_base;

bool person_store(repository_base *repository, const person_t *person);
bool person_store_list(repository_base *repository, const person_t *person_list, int items_amount);
bool person_recover_list(repository_base *repository, person_t **person_list, int *items_amount);

#endif /* REPOSITORY_H */
