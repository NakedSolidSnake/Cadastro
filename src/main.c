#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <menu.h>

int main(void)
{
    int option;
    while(true)
    {
        menu_print();
        scanf("%d", &option);
        getchar();
        menu_option_select(option);
    }
    
    return EXIT_SUCCESS;
}
