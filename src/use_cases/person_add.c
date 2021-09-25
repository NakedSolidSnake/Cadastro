#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <database.h>
#include <person.h>

void use_case_person_add_new(void)
{
    person_t person;
    FILE *f;

    person = person_create();

    if(db_is_database_exists() == false)
    {
        f = fopen(DB_DATABASE_FILE, "w");
    }
    else 
    {
        f = fopen(DB_DATABASE_FILE, "a");
    }

    char format[250] = "";
    snprintf(format, 250, DB_DATABASE_FORMAT, person.name, person.address, person.age);
    fprintf(f, "%s", format);
    fclose(f);
}