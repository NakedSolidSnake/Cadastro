#include <repository_factory.h>
#include <stdlib.h>
#include <string.h>
#include <file_database.h>
#include <sqlite_database.h>

// const char *types[] = 
// {
//     "file",
//     "sqlite"
// };

typedef struct 
{
    const char *name;
    repository_base *(*database_create)(void);
    bool (*database_destroy)(repository_base *repository);
} database_t;

database_t databases[] = 
{
    {.name = "file",   .database_create = file_create_database,   .database_destroy = file_destroy_database},
    {.name = "sqlite", .database_create = sqlite_create_database, .database_destroy = sqlite_destroy_database},
};

const unsigned int database_amount = sizeof(databases) / sizeof(databases[0]);

repository_base *repository_create(const char *type)
{
    repository_base *repository = NULL;

    for(int i = 0; i < database_amount; i++)
    {
         if(strncmp(databases[i].name, type, strlen(databases[i].name)) == 0)
        {
            repository = databases[i].database_create();
            break;
        }
    }

    return repository;
}

bool repository_destroy(const char *type, repository_base *repository)
{
    bool status = false;
    if(repository != NULL)
    {
        for (int i = 0; i < database_amount; i++)
        {
            if (strncmp(databases[i].name, type, strlen(databases[i].name)) == 0)
            {
                status = databases[i].database_destroy(repository);
                break;
            }
        }
    }
    return status;
}