#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <menu.h>
#include <repository_factory.h>

#define REPOSITORY_TYPE "sqlite"
// #define REPOSITORY_TYPE "file"

int main(void)
{
    int option;

    // repository_base *repository = repository_create("file");
    repository_base *repository = repository_create(REPOSITORY_TYPE);
    if(repository == NULL)
        return EXIT_FAILURE;

    while(true)
    {
        menu_print();
        scanf("%d", &option);
        getchar();
        menu_option_select(option, repository);
    }

    // free(repository);
    repository_destroy(REPOSITORY_TYPE, repository);
    
    return EXIT_SUCCESS;
}
