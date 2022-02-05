#include <person_service.h>
#include <string.h>
#include <stdlib.h>

static bool person_service_add (void *object, person_t *person);
static bool person_service_remove (void *object, person_t *person);
static bool person_service_update (void *object, person_t *person);
static bool person_service_find (void *object, person_t *person);
static bool person_service_getall (void *object, person_t **person_list, unsigned int *amount);

bool person_service_init (person_service_t *service)
{
    bool status = false;

    if (service != NULL)
    {
        memset (service, 0, sizeof (person_service_t));

        service->base.object = service;

        service->base.add    = person_service_add;
        service->base.remove = person_service_remove;
        service->base.update = person_service_update;
        service->base.find   = person_service_find;
        service->base.getall = person_service_getall;

        status = true;
    }

    return status;
}

bool person_service_open (person_service_t *service, person_repository_base_t *repository)
{
    bool status = false;

    if (service != NULL && repository != NULL)
    {
        service->repository = repository;

        status = true;
    }

    return status;
}

bool person_service_close (person_service_t *service)
{
     bool status = false;

    if (service != NULL)
    {
        memset (service, 0, sizeof (person_service_t));

        status = true;
    }

    return status;
}

static bool person_service_add (void *object, person_t *person)
{
    bool status = false;
    person_service_t *service = (person_service_t *)object;

    status = service->repository->add (service->repository->object, person);

    return status;
}

static bool person_service_remove (void *object, person_t *person)
{
    bool status = false;
    person_service_t *service = (person_service_t *)object;

    status = service->repository->remove (service->repository->object, person);

    return status;
}

static bool person_service_update (void *object, person_t *person)
{
    bool status = false;
    person_service_t *service = (person_service_t *)object;

    status = service->repository->update (service->repository->object, person);

    return status;
}

static bool person_service_find (void *object, person_t *person)
{
    bool status = false;
    person_service_t *service = (person_service_t *)object;

    status = service->repository->find (service->repository->object, person);

    return status;
}

static bool person_service_getall (void *object, person_t **person_list, unsigned int *amount)
{
    bool status = false;
    person_service_t *service = (person_service_t *)object;

    status = service->repository->getall (service->repository->object, person_list, amount);

    return status;
}