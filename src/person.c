#include <person.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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