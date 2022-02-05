#ifndef PERSON_REPOSITORY_SQLITE_H_
#define PERSON_REPOSITORY_SQLITE_H_

#include <person_repository_base.h>

#define SQLITE_BUFFER_SIZE  4096

typedef struct 
{
    person_repository_base_t base;
    const char *database_name;
    void *connection;
} person_repository_sqlite_t;

bool person_repository_sqlite_init (person_repository_sqlite_t *sqlite);
bool person_repository_sqlite_open (person_repository_sqlite_t *sqlite);
bool person_repository_sqlite_close (person_repository_sqlite_t *sqlite);

person_repository_base_t person_repository_sqlite_create (void);

#endif /* PERSON_REPOSITORY_SQLITE_H_ */
