#ifndef MENU_H
#define MENU_H

#include <stdbool.h>
#include <repository.h>

#define MENU_TEXT_ADD_PERSON     "1. Add a new person"
#define MENU_TEXT_REMOVE_PERSON  "2. Remove a person"
#define MENU_TEXT_UPDATE_PERSON  "3. Update a person"
#define MENU_TEXT_LIST_PERSON    "4. List all persons"
#define MENU_TEXT_FIND_PERSON    "5. Find a person"
#define MENU_TEXT_EXIT           "6. exit program"
#define MENU_TEXT_CURSOR         "> "

typedef enum 
{
    menu_option_add = 1,
    menu_option_remove,
    menu_option_update,
    menu_option_list,
    menu_option_find,
    menu_option_quit
} menu_option_t;

typedef void (*menu_option_base)(repository_base *repository);

typedef struct 
{
    menu_option_t option;
    menu_option_base command;
} menu_options_struct_t;

bool menu_option_select(int option, repository_base *repository);
void menu_print(void);
#endif /* MENU_H */
