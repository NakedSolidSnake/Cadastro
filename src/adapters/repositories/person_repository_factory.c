#include <person_repository_factory.h>
#include <person_repository_file.h>
#include <person_repository_sqlite.h>
#include <configuration.h>
#include <string.h>


person_repository_base_t person_repository_create (const char *type)
{
    person_repository_base_t base;

    // if (type == person_repository_type_file)
    if (strcmp (type, CONFIGURATION_REPOSITORY_TYPE_FILE) == 0)
    {
        base = person_repository_file_create ();
    }

    // if (type == person_repository_type_sqlite)
    if (strcmp (type, CONFIGURATION_REPOSITORY_TYPE_SQLITE) == 0)
    {
        base = person_repository_sqlite_create ();
    }

    return base;
}