#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <menu.h>
#include <repository_factory.h>
#include <view_factory.h>
#include <application.h>

#define REPOSITORY_TYPE "sqlite"
#define VIEW_TYPE       "cli"
// #define REPOSITORY_TYPE "file"

int main(void)
{
    // int option;
    repository_base *repository = NULL;
    view_base *view = NULL;
    application_t app;
    bool ret;

    do 
    {
        repository = repository_create(REPOSITORY_TYPE);
        if(repository == NULL)
            break;

        view = view_create(VIEW_TYPE);
        if (view == NULL)
            break;
        
        ret = application_init(&app, view, repository);
        if (ret == false)
            break;

        application_run(&app);

    } while (false);

    // repository_base *repository = repository_create("file");
    // repository_base *
    

    // while(true)
    // {
    //     menu_print();
    //     scanf("%d", &option);
    //     getchar();
    //     menu_option_select(option, repository);
    // }

    // free(repository);
    repository_destroy(REPOSITORY_TYPE, repository);
    view_destroy(VIEW_TYPE, view);
    
    return EXIT_SUCCESS;
}
