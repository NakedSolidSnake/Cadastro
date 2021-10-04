#include <repository_factory.h>
#include <stdlib.h>
#include <string.h>
#include <file_database.h>

const char *types[] = 
{
    "file"
};


repository_base *repository_create(const char *type)
{
    repository_base *repository = NULL;

    if(strncmp(types[0], type, strlen(types[0])) == 0)
    {
        repository = file_create_database();
    }

    return repository;
}