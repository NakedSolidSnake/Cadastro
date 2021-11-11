#include "sqlite_database.h"
#include <stdlib.h>
#include <sqlite3.h>
#include <stdio.h>
#include <string.h>

typedef struct 
{
    const char *database_name;
    sqlite3 *connection;
} sqlite_context;

typedef struct 
{
    person_t *list;
    int amount;
} sqlite_person_t;

static bool sqlite_database_open(sqlite_context *ctx);
static bool sqlite_prepare_table(sqlite_context *ctx);
static bool sqlite_insert(sqlite_context *ctx, const person_t *person);
static bool sqlite_update(sqlite_context *ctx, const person_t *person);
static bool sqlite_delete(sqlite_context *ctx, const person_t *person);
static int sqlite_get_items_amount(sqlite_context *ctx);
static int select_callback(void *user_data, int columns, char **columns_data, char **columns_name);

static bool sqlite_store(void *object, store_action_t *store);
static bool sqlite_recover_list(void *object, person_t **person_list, int *items_amount);

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

repository_base *sqlite_create_database(void)
{
    repository_base *repository = (repository_base *)malloc(sizeof(repository_base));
    if(repository)
    {
        sqlite_context *ctx = (sqlite_context *)malloc(sizeof(sqlite_context));
        if(ctx)
        {
            ctx->database_name = "person_database.db";
            repository->object = ctx;            
            repository->store = sqlite_store;
            repository->recover_list = sqlite_recover_list;
        }
        else 
        {
            free(repository);
            repository = NULL;
        }
        
    }

    return repository;
}

bool sqlite_destroy_database(repository_base *repository)
{
    bool status = false;

    if(repository)
    {
        sqlite_context *ctx = (sqlite_context *)repository->object;
        sqlite3_close(ctx->connection);
        free(repository->object);
        free(repository);
        status = true;
    }

    return status;
}

static bool sqlite_store(void *object, store_action_t *store)
{
    bool status = false;
    sqlite_context *ctx = (sqlite_context *)object;

    sqlite_prepare_table(object);

    switch (store->action)
    {
    case repo_insert:
        status = sqlite_insert(ctx, store->person);
        break;

    case repo_delete:
        status = sqlite_delete(ctx, &store->person[store->id]);
        break;

    case repo_update:
        status = sqlite_update(ctx, &store->person[store->id]);
        break;   
    default:
        break;
    }
    return status; 
}

static bool sqlite_recover_list(void *object, person_t **person_list, int *items_amount)
{
    int ret;
    bool status = false;
    sqlite_context *ctx = (sqlite_context *)object;
    char *query = "SELECT * FROM PERSON_TB";
    char *error_msg;

    sqlite_person_t sql_person = {.amount = 0};

    sqlite_prepare_table(ctx);

    do 
    {
        *items_amount = sqlite_get_items_amount(ctx);
        if(*items_amount <= 0)
            break;

        sql_person.list = (person_t *)malloc(sizeof(person_t) * (*items_amount));
        if(sql_person.list == NULL)
            break;

        sqlite_database_open(ctx);

        ret = sqlite3_exec(ctx->connection, query, select_callback, &sql_person, &error_msg);
        if(ret != SQLITE_OK)
        {
            fprintf(stderr, "SQL Error: %s\n", error_msg);
            sqlite3_free(error_msg);
            break;
        }

        *person_list = sql_person.list;

    } while(false);

    sqlite3_close(ctx->connection);

    return status;
}

static bool sqlite_database_open(sqlite_context *ctx)
{
    bool status =  true;

    int ret = sqlite3_open(ctx->database_name, &ctx->connection);
    if(ret)
    {
        fprintf(stderr, "It was not possible to open database %s\n", ctx->database_name);
        status = false;
    }

    return status;
}

static bool sqlite_prepare_table(sqlite_context *ctx)
{
    bool status = true;
    int ret;
    char *error_msg;
    char *sql = "CREATE TABLE IF NOT EXISTS PERSON_TB(" \
                "ID INTEGER PRIMARY KEY AUTOINCREMENT," \
                "NAME TEXT NOT NULL," \
                "ADDRESS TEXT NOT NULL," \
                "AGE INT NOT NULL);";

    sqlite_database_open(ctx);

    ret = sqlite3_exec(ctx->connection, sql, NULL, 0, &error_msg);
    if(ret != SQLITE_OK)
    {
        sqlite3_free(error_msg);
        status = false;
    }

    sqlite3_close(ctx->connection);
    return status;
}

static bool sqlite_insert(sqlite_context *ctx, const person_t *person)
{
    bool status = true;
    int ret;
    char *error_msg;
    char *query = "INSERT INTO PERSON_TB(NAME, ADDRESS, AGE) VALUES ('%s', '%s', %d);";
    char buffer_sql[SQLITE_BUFFER_SIZE] = {0};
    snprintf(buffer_sql, SQLITE_BUFFER_SIZE, query, person->name, person->address, person->age);

    sqlite_database_open(ctx);

    ret = sqlite3_exec(ctx->connection, buffer_sql, NULL, 0, &error_msg);
    if(ret != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", error_msg);
        sqlite3_free(error_msg);
        status = false;
    }

    sqlite3_close(ctx->connection);

    return status;
}

static bool sqlite_update(sqlite_context *ctx, const person_t *person)
{
    bool status = true;
    int ret;
    char *error_msg;
    char *query = "UPDATE PERSON_TB SET  NAME = '%s', ADDRESS = '%s', AGE = %d WHERE ID = %d;";
    char buffer_sql[SQLITE_BUFFER_SIZE] = {0};
    snprintf(buffer_sql, SQLITE_BUFFER_SIZE, query, person->name, person->address, person->age, person->id);

    sqlite_database_open(ctx);

    ret = sqlite3_exec(ctx->connection, buffer_sql, NULL, 0, &error_msg);
    if(ret != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", error_msg);
        sqlite3_free(error_msg);
        status = false;
    }

    sqlite3_close(ctx->connection);

    return status;
}

static bool sqlite_delete(sqlite_context *ctx, const person_t *person)
{
    bool status = true;
    int ret;
    char *error_msg;
    char *query = "DELETE FROM PERSON_TB WHERE ID = %d;";
    char buffer_sql[SQLITE_BUFFER_SIZE] = {0};
    snprintf(buffer_sql, SQLITE_BUFFER_SIZE, query, person->id);

    sqlite_database_open(ctx);

    ret = sqlite3_exec(ctx->connection, buffer_sql, NULL, 0, &error_msg);
    if(ret != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", error_msg);
        sqlite3_free(error_msg);
        status = false;
    }

    sqlite3_close(ctx->connection);

    return status;
}

static int sqlite_get_items_amount(sqlite_context *ctx)
{
   int rc;
   char *query;
   sqlite3_stmt *stmt;
   int row_count = -1;

   sqlite_database_open(ctx);

   query = "SELECT COUNT(*) FROM PERSON_TB";

   do 
   {
       rc = sqlite3_prepare_v2(ctx->connection, query, -1, &stmt, NULL);
       if(rc != SQLITE_OK)
           break;

        rc = sqlite3_step(stmt);
        if(rc != SQLITE_ROW)
           break;

        row_count = sqlite3_column_int(stmt, 0);
   } while(false);

   sqlite3_finalize(stmt);
   sqlite3_close(ctx->connection);

    return row_count;
}