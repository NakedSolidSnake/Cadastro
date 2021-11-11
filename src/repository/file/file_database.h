#ifndef FILE_DATABASE_H_
#define FILE_DATABASE_H_

#include <repository.h>
#include <stdbool.h>

#define DB_DATABASE_FORMAT     "%s, %s, %d\n"
#define DB_DATABASE_FILE       "database.txt"

repository_base *file_create_database(void);
bool file_destroy_database(repository_base *repository);

#endif /* FILE_DATABASE_H_ */
