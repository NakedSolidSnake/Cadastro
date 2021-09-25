#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <database.h>
#include <person.h>

void use_case_person_delete(void)
{
    int items = db_count_items();

    person_t *persons = (person_t *)malloc(sizeof(person_t) * items);
    if(persons == NULL)
        return;

    FILE *f = fopen(DB_DATABASE_FILE, "r");

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

    f = fopen(DB_DATABASE_FILE, "w");
    for(int i = 0; i < items; i++)
    {
        if(persons[i].name[0] == '\0' || persons[i].address[0] == '\0')
            continue;

        fprintf(f, DB_DATABASE_FORMAT, persons[i].name, persons[i].address, persons[i].age);
    }

    free(name_delete);
    free(persons);
    fclose(f);
}