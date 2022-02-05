#ifndef PERSON_SERVICE_H_
#define PERSON_SERVICE_H_

#include <person_service_base.h>
#include <person_repository_base.h>

typedef struct 
{
    person_service_base_t base;
    person_repository_base_t *repository;
} person_service_t;

bool person_service_init (person_service_t *service);
bool person_service_open (person_service_t *service, person_repository_base_t *repository);
bool person_service_close (person_service_t *service);

#endif /* PERSON_SERVICE_H_ */
