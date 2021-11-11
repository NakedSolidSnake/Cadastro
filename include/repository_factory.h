#ifndef REPOSITORY_FACTORY_H
#define REPOSITORY_FACTORY_H

#include <repository.h>
#include <stdbool.h>

repository_base *repository_create(const char *type);
bool repository_destroy(const char *type, repository_base *repository);

#endif /* REPOSITORY_FACTORY_H */
