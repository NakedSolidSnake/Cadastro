#include <menu.h>
#include <stdio.h>
#include <use_cases.h>

static menu_options_struct_t options[] = 
    {
        {.option = menu_option_add,    .command = use_case_person_add_new},
        {.option = menu_option_remove, .command = use_case_person_delete},
        {.option = menu_option_update, .command = use_case_person_update},
        {.option = menu_option_list,   .command = use_case_person_list},
        {.option = menu_option_find,   .command = use_case_person_find},
        {.option = menu_option_quit,   .command = use_case_person_quit}
    };

void menu_print(void)
{
    printf("%s\n", MENU_TEXT_ADD_PERSON);
    printf("%s\n", MENU_TEXT_REMOVE_PERSON);
    printf("%s\n", MENU_TEXT_UPDATE_PERSON);
    printf("%s\n", MENU_TEXT_LIST_PERSON);
    printf("%s\n", MENU_TEXT_FIND_PERSON);
    printf("%s\n", MENU_TEXT_EXIT);
    printf("%s",   MENU_TEXT_CURSOR);    
}

bool menu_option_select(int option, repository_base *repository)
{
    bool status = true;

    int list_size = sizeof(options) / sizeof(options[0]);

    for (int i = 0; i < list_size; i++)
    {
        if(option == options[i].option)
        {
            options[i].command(repository);
            break;
        }
    }

    return status;
}