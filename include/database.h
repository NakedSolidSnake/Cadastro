#ifndef DATABASE_H
#define DATABASE_H
#include <stdbool.h>

#define DB_DATABASE_FORMAT     "%s, %s, %d\n"
#define DB_DATABASE_FILE       "database.txt"

bool db_is_database_exists(void);
int db_count_items(void);

#endif /* DATABASE_H */
