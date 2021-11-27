#include "cli.h"
#include <stdlib.h>
#include <stdio.h>
#include <menu.h>

static bool cli_view_init(void *object);
static bool cli_view_exec(void *object, repository_base *repository);

view_base *cli_view_create(void)
{
    view_base *view = (view_base *)malloc(sizeof(view_base));
    if(view)
    {
        view->object = NULL;
        view->init = cli_view_init;
        view->exec = cli_view_exec;
    }

    return view;
}

bool cli_view_destroy(view_base *view)
{
    bool status = false;

    if (view)
    {
        free(view);
        status = true;
    }

    return status;
}

static bool cli_view_init(void *object)
{
    (void)object;
    return true;
}

static bool cli_view_exec(void *object, repository_base *repository)
{
    int option;

    while(true)
    {
        menu_print();
        scanf("%d", &option);
        getchar();
        menu_option_select(option, repository);
    }

    return true;
}