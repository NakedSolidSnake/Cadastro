#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <person.h>


#define DATABASE    "database.txt"

#define TEXT_ADD_PERSON     "1. Add a new person"
#define TEXT_REMOVE_PERSON  "2. Remove a person"
#define TEXT_UPDATE_PERSON  "3. Update a person"
#define TEXT_LIST_PERSON    "4. List all persons"
#define TEXT_FIND_PERSON    "5. Find a person"
#define TEXT_EXIT           "6. exit program"
#define TEXT_CURSOR         "> "

void print_menu(void);
bool option_select(int option);
int count_items(void);

void person_add_new(void);
void person_delete(void);
void person_update(void);
void person_list(void);
void person_find(void);

bool is_database_exists(void);

int main(void)
{
    int option;
    do 
    {
        print_menu();
        scanf("%d", &option);
        getchar();
    } while(option_select(option));
    
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

    switch (option)
    {
    case 1:
        //call a funtion to add new user
        person_add_new();
        break;
    
    case 2:
        // call a function to remove a user
        person_delete();
        break;

    case 3:
        //call a function to update a user
        person_update();
        break;

    case 4:
        // call a function to list all users
        person_list();        
        break;

    case 5:
        // call a function to find a user
        person_find();        
        break;

    case 6:
        status = false;
        break;

    default:
        // show a message 
        break;
  
    }

    return status;
}

void person_add_new(void)
{
    person_t person;
    FILE *f;

    printf("Type a name: ");
    fgets(person.name, PERSON_NAME_LEN - 1, stdin);
    person.name[strlen(person.name) - 1] = 0;

    printf("Type an address: ");
    fgets(person.address, PERSON_ADDRESS_LEN - 1, stdin);
    person.address[strlen(person.address) - 1] = 0;

    printf("Type an age: ");
    scanf("%d", &person.age);
    getchar();

    if(is_database_exists() == false)
    {
        f = fopen(DATABASE, "w");
    }
    else 
    {
        f = fopen(DATABASE, "a");
    }

    char format[250] = "";
    snprintf(format, 250, "%s, %s, %d\n", person.name, person.address, person.age);
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

        char *data = strtok(buffer, ",");
        strncpy(persons[i].name, data, PERSON_NAME_LEN);
        data = strtok(NULL, ",");
        strncpy(persons[i].address, data, PERSON_ADDRESS_LEN);
        data = strtok(NULL, ",");
        persons[i].age = atoi(data);
    }

    fclose(f);

    char name_delete[PERSON_NAME_LEN] = "";
    printf("Type a name to delete: ");
    fgets(name_delete, PERSON_NAME_LEN - 1, stdin);
    name_delete[strlen(name_delete) - 1] = 0;

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

        fprintf(f, "%s, %s, %d\n", persons[i].name, persons[i].address, persons[i].age);
    }

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

        char *data = strtok(buffer, ",");
        strncpy(persons[i].name, data, PERSON_NAME_LEN);
        data = strtok(NULL, ",");
        strncpy(persons[i].address, data, PERSON_ADDRESS_LEN);
        data = strtok(NULL, ",");
        persons[i].age = atoi(data);
    }

    fclose(f);

    char name_update[PERSON_NAME_LEN] = "";
    printf("Type a name to update: ");
    fgets(name_update, PERSON_NAME_LEN - 1, stdin);
    name_update[strlen(name_update) - 1] = 0;

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

        printf("Type a name: ");
        fgets(persons[id].name, PERSON_NAME_LEN - 1, stdin);
        persons[id].name[strlen(persons[id].name) - 1] = 0;

        printf("Type an address: ");
        fgets(persons[id].address, PERSON_ADDRESS_LEN - 1, stdin);
        persons[id].address[strlen(persons[id].address) - 1] = 0;

        printf("Type an age: ");
        scanf("%d", &persons[id].age);
        getchar();
    }

    f = fopen(DATABASE, "w");
    for(int i = 0; i < items; i++)
    {
        if(persons[i].name[0] == '\0' || persons[i].address[0] == '\0')
            continue;

        fprintf(f, "%s, %s, %d\n", persons[i].name, persons[i].address, persons[i].age);
    }

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
    char name_find[PERSON_NAME_LEN] = "";
    printf("Type a name to find: ");
    fgets(name_find, PERSON_NAME_LEN - 1, stdin);
    name_find[strlen(name_find) - 1] = 0;

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