#include <person_repository_factory.h>
#include <person_repository_file.h>
#include <person_repository_sqlite.h>


person_repository_base_t person_repository_create (person_repository_type_t type)
{
    person_repository_base_t base;

    if (type == person_repository_type_file)
    {
        base = person_repository_file_create ();
    }

    if (type == person_repository_type_sqlite)
    {
        base = person_repository_sqlite_create ();
    }

    return base;
}