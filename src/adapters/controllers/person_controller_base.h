#ifndef PERSON_CONTROLLER_BASE_H_
#define PERSON_CONTROLLER_BASE_H_

#include <person_service.h>

typedef struct 
{
    person_service_t *service;
    int argc;
    char **argv;
} person_controller_args_t;

typedef struct 
{
    void *object;
    bool (*init) (void *object);
    bool (*open) (void *object, person_controller_args_t *args);
    bool (*run) (void *object);
    bool (*close) (void *object);
} person_controller_base_t;

#endif /* PERSON_CONTROLLER_BASE_H_ */
