#include <stdio.h>
#include <database.h>


void use_case_person_list(void)
{
    FILE *f;

    if(db_is_database_exists())
    {
        f = fopen(DB_DATABASE_FILE, "r");
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