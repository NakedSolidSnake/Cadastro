#include <repository.h>

bool person_store(repository_base *repository, const person_t *person)
{
    return repository->store(repository->object, person);
}

bool person_store_list(repository_base *repository, const person_t *person_list, int items_amount)
{
    return repository->store_list(repository->object, person_list, items_amount);
}

bool person_recover_list(repository_base *repository, person_t **person_list, int *items_amount)
{
    return repository->recover_list(repository->object, person_list, items_amount);
}