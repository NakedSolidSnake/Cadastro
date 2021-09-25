#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <person.h>

#define DATABASE_FORMAT     "%s, %s, %d\n"
#define DATABASE            "database.txt"

#define TEXT_ADD_PERSON     "1. Add a new person"
#define TEXT_REMOVE_PERSON  "2. Remove a person"
#define TEXT_UPDATE_PERSON  "3. Update a person"
#define TEXT_LIST_PERSON    "4. List all persons"
#define TEXT_FIND_PERSON    "5. Find a person"
#define TEXT_EXIT           "6. exit program"
#define TEXT_CURSOR         "> "

typedef enum 
{
    option_add = 1,
    option_remove,
    option_update,
    option_list,
    option_find,
    option_quit
} option_t;

typedef void (*option_base)(void);

typedef struct 
{
    option_t option;
    option_base command;
} options_struct_t;

person_t person_create(void);
char *person_input_name(void);
void person_parser(char *buffer, person_t *person);

void print_menu(void);
bool option_select(int option);
int count_items(void);

void person_add_new(void);
void person_delete(void);
void person_update(void);
void person_list(void);
void person_find(void);
void person_quit(void);

bool is_database_exists(void);

int main(void)
{
    int option;
    while(true)
    {
        print_menu();
        scanf("%d", &option);
        getchar();
        option_select(option);
    }
    
    return EXIT_SUCCESS;
}

void print_menu(void)
{
    printf("%s\n", TEXT_ADD_PERSON);
    printf("%s\n", TEXT_REMOVE_PERSON);
    printf("%s\n", TEXT_UPDATE_PERSON);
    printf("%s\n", TEXT_LIST_PERSON);
    printf("%s\n", TEXT_FIND_PERSON);
    printf("%s\n", TEXT_EXIT);
    printf("%s", TEXT_CURSOR);    
}

bool option_select(int option)
{
    bool status = true;

    options_struct_t options[] = 
    {
        {.option = option_add,    .command = person_add_new},
        {.option = option_remove, .command = person_delete},
        {.option = option_update, .command = person_update},
        {.option = option_list,   .command = person_list},
        {.option = option_find,   .command = person_find},
        {.option = option_quit,   .command = person_quit}
    };

    int list_size = sizeof(options) / sizeof(options[0]);

    for (int i = 0; i < list_size; i++)
    {
        if(option == options[i].option)
        {
            options[i].command();
            break;
        }
    }

    return status;
}

void person_add_new(void)
{
    person_t person;
    FILE *f;

    person = person_create();

    if(is_database_exists() == false)
    {
        f = fopen(DATABASE, "w");
    }
    else 
    {
        f = fopen(DATABASE, "a");
    }

    char format[250] = "";
    snprintf(format, 250, DATABASE_FORMAT, person.name, person.address, person.age);
    fprintf(f, "%s", format);
    fclose(f);
}

void person_delete(void)
{
    int items = count_items();

    person_t *persons = (person_t *)malloc(sizeof(person_t) * items);
    if(persons == NULL)
        return;

    FILE *f = fopen(DATABASE, "r");

    for(int i = 0; i < items; i++)
    {
        char buffer[240] = "";
        fgets(buffer, 240, f);

        person_parser(buffer, &persons[i]);
    }

    fclose(f);

    char *name_delete = person_input_name();

    for(int i = 0; i < items; i++)
    {
        if(strncmp(name_delete, persons[i].name, PERSON_NAME_LEN) == 0)
        {
            memset(&persons[i], 0, sizeof(person_t));
            break;
        }
    }

    f = fopen(DATABASE, "w");
    for(int i = 0; i < items; i++)
    {
        if(persons[i].name[0] == '\0' || persons[i].address[0] == '\0')
            continue;

        fprintf(f, DATABASE_FORMAT, persons[i].name, persons[i].address, persons[i].age);
    }

    free(name_delete);
    free(persons);
    fclose(f);
}

void person_update(void)
{
    int id = -1;
    int items = count_items();

    person_t *persons = (person_t *)malloc(sizeof(person_t) * items);
    if(persons == NULL)
        return;

    FILE *f = fopen(DATABASE, "r");

    for(int i = 0; i < items; i++)
    {
        char buffer[240] = "";
        fgets(buffer, 240, f);

        person_parser(buffer, &persons[i]);

    }

    fclose(f);

    char *name_update = person_input_name();

    for (int i = 0; i < items; i++)
    {
        if(strncmp(name_update, persons[i].name, PERSON_NAME_LEN) == 0)
        {
            id = i;
            break;
        }
    }
    
    if(id != -1)
    {
        memset(&persons[id], 0, sizeof(person_t));
        persons[id] = person_create();
    }

    f = fopen(DATABASE, "w");
    for(int i = 0; i < items; i++)
    {
        if(persons[i].name[0] == '\0' || persons[i].address[0] == '\0')
            continue;

        fprintf(f, DATABASE_FORMAT, persons[i].name, persons[i].address, persons[i].age);
    }

    free(name_update);
    free(persons);
    fclose(f);    
}

void person_list(void)
{
    FILE *f;

    if(is_database_exists())
    {
        f = fopen(DATABASE, "r");
    }
    else 
        return;

    char c = fgetc(f);
    while(c != EOF)
    {
        printf("%c", c);
        c = fgetc(f);
    }

    fclose(f);
}

void person_find(void)
{
    char *name_find = person_input_name();    

    if(is_database_exists())
    {
        FILE *f = fopen(DATABASE, "r");

        fseek(f, 0, SEEK_END);
        long size = ftell(f);
        rewind(f);

        char *buffer = calloc(1, size + 1);
        size_t  len = fread(buffer, sizeof(char), size, f);
        if(ferror(f) != 0)
        {
            //erro
        }
        else 
        {
            buffer[len + 1] = '\0';
        }

        char *name_encounter = strstr(buffer, name_find);
        if(name_encounter != NULL)
        {
            char c;
            for(int i = 0; ; i++)
            {
                c = name_encounter[i];
                if(c == '\n')
                    break;
                else 
                    putc(c, stdout);
            }
            putc('\n', stdout);
        }
        free(name_find);
        free(buffer);
        fclose(f);
    }
}

bool is_database_exists(void)
{
    bool status = false;

    FILE *f = fopen(DATABASE, "r");
    if(f != NULL)
    {
        fclose(f);
        status = true;
    }

    return status;
}

int count_items(void)
{
    FILE *f;
    int items = 0;

    if(is_database_exists())
    {
        f = fopen(DATABASE, "r");
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

person_t person_create(void)
{
    person_t person;
    printf("Type a name: ");
    fgets(person.name, PERSON_NAME_LEN - 1, stdin);
    person.name[strlen(person.name) - 1] = 0;

    printf("Type an address: ");
    fgets(person.address, PERSON_ADDRESS_LEN - 1, stdin);
    person.address[strlen(person.address) - 1] = 0;

    printf("Type an age: ");
    scanf("%d", &person.age);
    getchar();

    return person;
}

char *person_input_name(void)
{
    char *name = calloc(1, PERSON_NAME_LEN + 1);    
    printf("Type a name to modify: ");
    fgets(name, PERSON_NAME_LEN - 1, stdin);
    name[strlen(name) - 1] = 0;
    return name;
}

void person_parser(char *buffer, person_t *person)
{
    if(person == NULL || buffer == NULL)
        return ;

    char *data = strtok(buffer, ",");
    strncpy(person->name, data, PERSON_NAME_LEN);
    data = strtok(NULL, ",");
    strncpy(person->address, data, PERSON_ADDRESS_LEN);
    data = strtok(NULL, ",");
    person->age = atoi(data);
}

void person_quit(void)
{
    exit(0);
}