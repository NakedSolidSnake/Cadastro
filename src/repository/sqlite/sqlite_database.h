#ifndef SQLITE_DATABASE_H_
#define SQLITE_DATABASE_H_

#include <repository.h>
#include <stdbool.h>

#define SQLITE_BUFFER_SIZE  4096

typedef enum 
{
    id_pos = 0,
    name_pos,
    address_pos,
    age_pos
} column_pos;

repository_base *sqlite_create_database(void);
bool sqlite_destroy_database(repository_base *repository);

#endif /* SQLITE_DATABASE_H_ */
