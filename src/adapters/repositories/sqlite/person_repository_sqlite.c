#include <person_repository_sqlite.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <string.h>
#include <stdio.h>

typedef enum 
{
    id_pos = 0,
    name_pos,
    address_pos,
    age_pos
} column_pos;

typedef struct 
{
    person_t *list;
    int amount;
} sqlite_person_t;

static bool sqlite_database_open (person_repository_sqlite_t *sqlite);
static bool sqlite_prepare_table (person_repository_sqlite_t *sqlite);
static int sqlite_get_items_amount (person_repository_sqlite_t *sqlite);
static int select_callback (void *user_data, int columns, char **columns_data, char **columns_name);


static bool person_repository_sqlite_add (void *object, person_t *person);
static bool person_repository_sqlite_remove (void *object, person_t *person);
static bool person_repository_sqlite_update (void *object, person_t *person);
static bool person_repository_sqlite_find (void *object, person_t *person);
static bool person_repository_sqlite_getall (void *object, person_t **person_list, unsigned int *amount);

bool person_repository_sqlite_init (person_repository_sqlite_t *sqlite)
{
    bool status = false;

    if (sqlite != NULL)
    {
        memset (sqlite, 0, sizeof (person_repository_sqlite_t));

        sqlite->base.object = sqlite;

        sqlite->base.add    = person_repository_sqlite_add;
        sqlite->base.remove = person_repository_sqlite_remove;
        sqlite->base.update = person_repository_sqlite_update;
        sqlite->base.find   = person_repository_sqlite_find;
        sqlite->base.getall = person_repository_sqlite_getall;

        sqlite->database_name = "person_database.db";

        status = true;
    }

    return status;
}

bool person_repository_sqlite_open (person_repository_sqlite_t *sqlite)
{
    bool status = false;

    if (sqlite != NULL)
    {
        status = true;
    }

    return status;
}

bool person_repository_sqlite_close (person_repository_sqlite_t *sqlite)
{
    bool status = false;

    if (sqlite != NULL)
    {
        memset (sqlite, 0, sizeof (person_repository_sqlite_t));
        status = true;
    }

    return status;
}

person_repository_base_t person_repository_sqlite_create (void)
{
    static person_repository_sqlite_t sqlite;

    person_repository_sqlite_init (&sqlite);
    person_repository_sqlite_open (&sqlite);

    return sqlite.base;
}

static bool person_repository_sqlite_add (void *object, person_t *person)
{
    person_repository_sqlite_t *sqlite = (person_repository_sqlite_t *)object;
    bool status = true;
    int ret;
    char *error_msg;
    char *query = "INSERT INTO PERSON_TB(NAME, ADDRESS, AGE) VALUES ('%s', '%s', %d);";
    char buffer_sql[SQLITE_BUFFER_SIZE] = {0};
    snprintf(buffer_sql, SQLITE_BUFFER_SIZE, query, person->name, person->address, person->age);

    sqlite_database_open(sqlite);

    ret = sqlite3_exec(sqlite->connection, buffer_sql, NULL, 0, &error_msg);
    if(ret != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", error_msg);
        sqlite3_free(error_msg);
        status = false;
    }

    sqlite3_close(sqlite->connection);

    return status;
}

static bool person_repository_sqlite_remove (void *object, person_t *person)
{
    person_repository_sqlite_t *sqlite = (person_repository_sqlite_t *)object;
    bool status = true;
    int ret;
    char *error_msg;
    char *query = "DELETE FROM PERSON_TB WHERE ID = %d;";
    char buffer_sql[SQLITE_BUFFER_SIZE] = {0};
    snprintf(buffer_sql, SQLITE_BUFFER_SIZE, query, person->id);

    sqlite_database_open(sqlite);

    ret = sqlite3_exec(sqlite->connection, buffer_sql, NULL, 0, &error_msg);
    if(ret != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", error_msg);
        sqlite3_free(error_msg);
        status = false;
    }

    sqlite3_close(sqlite->connection);

    return status;
}

static bool person_repository_sqlite_update (void *object, person_t *person)
{
    person_repository_sqlite_t *sqlite = (person_repository_sqlite_t *)object;
    bool status = true;
    int ret;
    char *error_msg;
    char *query = "UPDATE PERSON_TB SET  NAME = '%s', ADDRESS = '%s', AGE = %d WHERE ID = %d;";
    char buffer_sql[SQLITE_BUFFER_SIZE] = {0};
    snprintf(buffer_sql, SQLITE_BUFFER_SIZE, query, person->name, person->address, person->age, person->id);

    sqlite_database_open(sqlite);

    ret = sqlite3_exec(sqlite->connection, buffer_sql, NULL, 0, &error_msg);
    if(ret != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", error_msg);
        sqlite3_free(error_msg);
        status = false;
    }

    sqlite3_close(sqlite->connection);

    return status;
}

static bool person_repository_sqlite_find (void *object, person_t *person)
{
    person_repository_sqlite_t *sqlite = (person_repository_sqlite_t *)object;
    bool status = false;

    person_t *person_list = NULL;
    unsigned int amount = 0;

    status = person_repository_sqlite_getall (sqlite, &person_list, &amount);

    if (status == true)
    {
        status = false;

        for (unsigned int i = 0; i < amount; i++)
        {
            char *found = strstr (person_list[i].name, person->name);
            if (found != NULL)
            {
                memcpy (person, &person_list[i], sizeof (person_t));
                status = true;
                break;
            }
        }

        free (person_list);
    }

    return status;
}

static bool person_repository_sqlite_getall (void *object, person_t **person_list, unsigned int *amount)
{
    person_repository_sqlite_t *sqlite = (person_repository_sqlite_t *)object;
    int ret;
    bool status = false;
    char *query = "SELECT * FROM PERSON_TB";
    char *error_msg;

    sqlite_person_t sql_person = {.amount = 0};

    sqlite_prepare_table(sqlite);

    do 
    {
        *amount = sqlite_get_items_amount(sqlite);
        if(*amount <= 0)
            break;

        sql_person.list = (person_t *)malloc(sizeof(person_t) * (*amount));
        if(sql_person.list == NULL)
            break;

        sqlite_database_open(sqlite);

        ret = sqlite3_exec(sqlite->connection, query, select_callback, &sql_person, &error_msg);
        if(ret != SQLITE_OK)
        {
            fprintf(stderr, "SQL Error: %s\n", error_msg);
            sqlite3_free(error_msg);
            break;
        }

        *person_list = sql_person.list;
        status = true;

    } while(false);

    sqlite3_close(sqlite->connection);

    return status;
}

static int select_callback(void *user_data, int columns, char **columns_data, char **columns_name)
{
    sqlite_person_t *person = (sqlite_person_t *)user_data;
    person->list[person->amount].id = atoi(columns_data[id_pos]);
    strncpy(person->list[person->amount].name, columns_data[name_pos], PERSON_NAME_LEN);
    strncpy(person->list[person->amount].address, columns_data[address_pos], PERSON_ADDRESS_LEN);
    person->list[person->amount].age = atoi(columns_data[age_pos]);

    person->amount++;
    return 0;
}

static bool sqlite_database_open (person_repository_sqlite_t *sqlite)
{
    bool status =  true;

    int ret = sqlite3_open (sqlite->database_name, (sqlite3 **)&sqlite->connection);
    if(ret)
    {
        fprintf (stderr, "It was not possible to open database %s\n", sqlite->database_name);
        status = false;
    }

    return status;
}

static bool sqlite_prepare_table (person_repository_sqlite_t *sqlite)
{
    bool status = true;
    int ret;
    char *error_msg;
    char *sql = "CREATE TABLE IF NOT EXISTS PERSON_TB(" \
                "ID INTEGER PRIMARY KEY AUTOINCREMENT," \
                "NAME TEXT NOT NULL," \
                "ADDRESS TEXT NOT NULL," \
                "AGE INT NOT NULL);";

    sqlite_database_open(sqlite);

    ret = sqlite3_exec(sqlite->connection, sql, NULL, 0, &error_msg);
    if(ret != SQLITE_OK)
    {
        sqlite3_free(error_msg);
        status = false;
    }

    sqlite3_close(sqlite->connection);
    return status;
}

static int sqlite_get_items_amount(person_repository_sqlite_t *sqlite)
{
   int rc;
   char *query;
   sqlite3_stmt *stmt;
   int row_count = -1;

   sqlite_database_open(sqlite);

   query = "SELECT COUNT(*) FROM PERSON_TB";

   do 
   {
       rc = sqlite3_prepare_v2(sqlite->connection, query, -1, &stmt, NULL);
       if(rc != SQLITE_OK)
           break;

        rc = sqlite3_step(stmt);
        if(rc != SQLITE_ROW)
           break;

        row_count = sqlite3_column_int(stmt, 0);
   } while(false);

   sqlite3_finalize(stmt);
   sqlite3_close(sqlite->connection);

    return row_count;
}