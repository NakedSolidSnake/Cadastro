#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <database.h>
#include <person.h>

void use_case_person_find(void)
{
    char *name_find = person_input_name();    

    if(db_is_database_exists())
    {
        FILE *f = fopen(DB_DATABASE_FILE, "r");

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