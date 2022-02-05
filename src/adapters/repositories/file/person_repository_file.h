#ifndef PERSON_REPOSITORY_FILE_H_
#define PERSON_REPOSITORY_FILE_H_

#include <person_repository_base.h>

#define DB_DATABASE_FORMAT     "%s, %s, %d\n"
#define DB_DATABASE_FILE       "database.txt"
#define DB_FORMAT_LEN          (PERSON_NAME_LEN + PERSON_ADDRESS_LEN + 40)

typedef struct 
{
    person_repository_base_t base;
    void *descriptor;
} person_repository_file_t;

bool person_repository_file_init (person_repository_file_t *file);
bool person_repository_file_open (person_repository_file_t *file);
bool person_repository_file_close (person_repository_file_t *file);

person_repository_base_t person_repository_file_create (void);

#endif /* PERSON_REPOSITORY_FILE_H_ */
