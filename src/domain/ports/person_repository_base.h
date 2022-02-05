#ifndef PERSON_REPOSITORY_BASE_H_
#define PERSON_REPOSITORY_BASE_H_

#include <stdbool.h>
#include <person.h>

typedef struct 
{
    void *object;
    bool (*add) (void *object, person_t *person);
    bool (*remove) (void *object, person_t *person);
    bool (*update) (void *object, person_t *person);
    bool (*find) (void *object, person_t *person);
    bool (*getall) (void *object, person_t **person_list, unsigned int *amount);
} person_repository_base_t;

#endif /* PERSON_REPOSITORY_BASE_H_ */
