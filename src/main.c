#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <menu.h>
#include <repository_factory.h>

int main(void)
{
    int option;

    repository_base *repository = repository_create("file");
    if(repository == NULL)
        return EXIT_FAILURE;

    while(true)
    {
        menu_print();
        scanf("%d", &option);
        getchar();
        menu_option_select(option, repository);
    }

    free(repository);
    
    return EXIT_SUCCESS;
}
