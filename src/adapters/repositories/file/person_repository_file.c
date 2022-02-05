#include <person_repository_file.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static bool person_repository_file_add (void *object, person_t *person);
static bool person_repository_file_remove (void *object, person_t *person);
static bool person_repository_file_update (void *object, person_t *person);
static bool person_repository_file_find (void *object, person_t *person);
static bool person_repository_file_getall (void *object, person_t **person_list, unsigned int *amount);

static bool person_repository_file_is_database_exists(void);
static unsigned int person_repository_file_count_items(void);
static bool person_repository_file_parser(const char *buffer, person_t *person);
static bool person_repository_file_write_all(const person_t *person_list, unsigned int items_amount);
static bool person_repository_file_read_all(person_t **person_list, unsigned int *items_amount);


bool person_repository_file_init (person_repository_file_t *file)
{
    bool status = false;

    if (file != NULL)
    {
        memset (file, 0, sizeof (person_repository_file_t));

        file->base.object = file;

        file->base.add    = person_repository_file_add;
        file->base.remove = person_repository_file_remove;
        file->base.update = person_repository_file_update;
        file->base.find   = person_repository_file_find;
        file->base.getall = person_repository_file_getall;

        status = true;
    }

    return status;
}

bool person_repository_file_open (person_repository_file_t *file)
{
    bool status = false;

    if (file != NULL)
    {
        status = true;
    }

    return status;
}

bool person_repository_file_close (person_repository_file_t *file)
{
    bool status = false;

    if (file != NULL)
    {
        memset (file, 0, sizeof (person_repository_file_t));
        status = true;
    }

    return status;
}

person_repository_base_t person_repository_file_create (void)
{
    static person_repository_file_t file;

    person_repository_file_init (&file);
    person_repository_file_open (&file);

    return file.base;
}

static bool person_repository_file_add (void *object, person_t *person)
{
    char format[DB_FORMAT_LEN + 1] = "";

    person_repository_file_t *file = (person_repository_file_t *)object;

    if(person_repository_file_is_database_exists() == false)
    {
        file->descriptor = (void *)fopen(DB_DATABASE_FILE, "w");
    }
    else 
    {
        file->descriptor = (void *)fopen(DB_DATABASE_FILE, "a");
    }
    
    snprintf(format, DB_FORMAT_LEN, DB_DATABASE_FORMAT, person->name, person->address, person->age);
    fprintf((FILE *)file->descriptor, "%s", format);
    fclose((FILE *)file->descriptor);

    return true;
}

static bool person_repository_file_remove (void *object, person_t *person)
{
    bool status = false;
    person_repository_file_t *file = (person_repository_file_t *)object;
    (void)file;
    person_t *person_list = NULL;
    unsigned int amount = 0;

    status = person_repository_file_read_all (&person_list, &amount);

    if (status == true)
    {
        status = false;

        for (unsigned int i = 0; i < amount; i++)
        {
            if (person->id == person_list[i].id)
            {
                memset (&person_list[i], 0, sizeof (person_t));
                person_repository_file_write_all (person_list, amount);
                free (person_list);
                status = true;
                break;
            }
        }
    }

    return status;
}

static bool person_repository_file_update (void *object, person_t *person)
{
    bool status = false;
    person_repository_file_t *file = (person_repository_file_t *)object;
    (void)file;
    person_t *person_list = NULL;
    unsigned int amount = 0;

    status = person_repository_file_read_all (&person_list, &amount);

    if (status == true)
    {
        status = false;

        for (unsigned int i = 0; i < amount; i++)
        {
            if (person->id == person_list[i].id)
            {
                memcpy (&person_list[i], person, sizeof (person_t));
                person_repository_file_write_all (person_list, amount);
                free (person_list);
                status = true;
                break;
            }
        }
    }

    return status;
}

static bool person_repository_file_find (void *object, person_t *person)
{
    bool status = false;
    person_repository_file_t *file = (person_repository_file_t *)object;
    (void)file;
    person_t *person_list = NULL;
    unsigned int amount = 0;

    status = person_repository_file_read_all (&person_list, &amount);

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

static bool person_repository_file_getall (void *object, person_t **person_list, unsigned int *amount)
{
    bool status = false;
    person_repository_file_t *file = (person_repository_file_t *)object;
    (void)file;
    unsigned int _amount = 0;

    status = person_repository_file_read_all (person_list, &_amount);

    if (status == true)
        *amount = _amount;

    return status;
}

static bool person_repository_file_write_all(const person_t *person_list, unsigned int items_amount)
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

static bool person_repository_file_read_all(person_t **person_list, unsigned int *items_amount)
{
    bool status = false;
    unsigned int items = person_repository_file_count_items ();
    *items_amount = items;

    person_t *_person_list = (person_t *)malloc(sizeof(person_t) * items);
    if(_person_list != NULL)
    {
        FILE *f = fopen(DB_DATABASE_FILE, "r");

        for(int i = 0; i < items; i++)
        {
            char buffer[DB_FORMAT_LEN] = "";
            fgets(buffer, DB_FORMAT_LEN, f);

            person_repository_file_parser(buffer, &_person_list[i]);
            _person_list[i].id = i;
        }

        *person_list = _person_list;

        fclose(f);

        status = true;
    }

    return status;
}

bool person_repository_file_is_database_exists(void)
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

static unsigned int person_repository_file_count_items(void)
{
    FILE *f;
    unsigned int items = 0;

    if(person_repository_file_is_database_exists() == true)
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

static bool person_repository_file_parser(const char *buffer, person_t *person)
{
    bool status = false;
    
    if(person != NULL && buffer != NULL)
    {
        char *temp = (char *)buffer;
        char *data = strtok(temp, ",");
        strncpy(person->name, data, PERSON_NAME_LEN);
        data = strtok(NULL, ",");
        strncpy(person->address, data, PERSON_ADDRESS_LEN);
        data = strtok(NULL, ",");
        person->age = atoi(data);

        status = true;
    }
        
    return status;    
}