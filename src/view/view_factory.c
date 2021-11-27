#include <view_base.h>
#include "cli/cli.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct 
{
    const char *name;
    view_base *(*view_create)(void);
    bool (*view_destroy)(view_base *view);
} view_t;

view_t views[] = 
{
    {.name = "cli", .view_create = cli_view_create, .view_destroy = cli_view_destroy},
};

static const unsigned int view_amount = sizeof(views) / sizeof(views[0]);

view_base *view_create(const char *type)
{
    view_base *view = NULL;

    for (int i = 0; i < view_amount; i++)
    {
        if (strncmp (views[i].name, type, strlen(views[i].name)) == 0)
        {
            view = views[i].view_create();
            break;
        }
    }

    return view;
}

bool view_destroy(const char *type, view_base *view)
{
    bool status = false;

    if (view != NULL)
    {
       for (int i = 0; i < view_amount; i++)
        {
            if (strncmp (views[i].name, type, strlen(views[i].name)) == 0)
            {
                status = views[i].view_destroy(view);
                break;
            }
        } 
    }

    return status;
}