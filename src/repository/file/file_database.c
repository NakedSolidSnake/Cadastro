#include "file_database.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static bool file_is_database_exists(void);
static int file_count_items(void);
static bool file_store(void *object, const person_t *person);
static bool file_store_list(void *object, const person_t *person_list, int items_amount);
static bool file_recover_list(void *object, person_t **person_list, int *items_amount);
static void person_parser(const char *buffer, person_t *person);

static bool file_store(void *object, const person_t *person)
{
    FILE *f;

    if(file_is_database_exists() == false)
    {
        f = fopen(DB_DATABASE_FILE, "w");
    }
    else 
    {
        f = fopen(DB_DATABASE_FILE, "a");
    }

    char format[250] = "";
    snprintf(format, 250, DB_DATABASE_FORMAT, person->name, person->address, person->age);
    fprintf(f, "%s", format);
    fclose(f);

    return true;
}

static bool file_store_list(void *object, const person_t *person_list, int items_amount)
{
    FILE *f;
    f = fopen(DB_DATABASE_FILE, "w");

    for(int i = 0; i < items_amount; i++)
    {
        if(person_list[i].name[0] == '\0' || person_list[i].address[0] == '\0')
            continue;

        fprintf(f, DB_DATABASE_FORMAT, person_list[i].name, person_list[i].address, person_list[i].age);
    }

    fclose(f);
    return true;
}

static bool file_recover_list(void *object, person_t **person_list, int *items_amount)
{
    int items = file_count_items();

    *items_amount = items;

    person_t *_person_list = (person_t *)malloc(sizeof(person_t) * items);
    if(_person_list == NULL)
        return false;

    FILE *f = fopen(DB_DATABASE_FILE, "r");

    for(int i = 0; i < items; i++)
    {
        char buffer[240] = "";
        fgets(buffer, 240, f);

        person_parser(buffer, &_person_list[i]);
    }

    *person_list = _person_list;
    fclose(f);

    return true;
}

repository_base *file_create_database(void)
{
    repository_base *repository = (repository_base *)malloc(sizeof(repository_base));
    if(repository)
    {
        repository->object = NULL;
        repository->store = file_store;
        repository->store_list = file_store_list;
        repository->recover_list = file_recover_list;
    }

    return repository;
}

bool file_is_database_exists(void)
{
    bool status = false;

    FILE *f = fopen(DB_DATABASE_FILE, "r");
    if(f != NULL)
    {
        fclose(f);
        status = true;
    }

    return status;
}

int file_count_items(void)
{
    FILE *f;
    int items = 0;

    if(file_is_database_exists())
    {
        f = fopen(DB_DATABASE_FILE, "r");
    }
    else 
        return -1;

    char c = fgetc(f);
    while(c != EOF)
    {
        if(c == '\n')
            items++;
        c = fgetc(f);
    }

    fclose(f);

    return items;
}

static void person_parser(const char *buffer, person_t *person)
{
    char *temp = (char *)buffer;
    if(person == NULL || buffer == NULL)
        return ;

    char *data = strtok(temp, ",");
    strncpy(person->name, data, PERSON_NAME_LEN);
    data = strtok(NULL, ",");
    strncpy(person->address, data, PERSON_ADDRESS_LEN);
    data = strtok(NULL, ",");
    person->age = atoi(data);
}