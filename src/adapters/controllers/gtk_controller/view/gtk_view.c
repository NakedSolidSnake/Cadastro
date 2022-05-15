#include "gtk_view.h"
#include <stdlib.h>
#include <string.h>

bool gtk_view_init (gtk_view_t *view)
{
    bool status = false;

    if (view != NULL)
    {
        memset (view, 0, sizeof (gtk_view_t));

        status = main_window_init (&view->main);
    }

    return status;
}

bool gtk_view_open (gtk_view_t *view, gtk_view_args_t *args)
{
    bool status = false;
    main_window_args_t main_args;

    if (view != NULL && args != NULL)
    {
        main_args.argc = args->argc;
        main_args.argv = args->argv;

        status = main_window_open (&view->main, &main_args);
    }

    return status;
}

bool gtk_view_run (gtk_view_t *view)
{
    bool status = false;

    if (view != NULL)
    {
        status = main_window_run (&view->main);
    }

    return status;
}

bool gtk_view_close (gtk_view_t *view)
{
    bool status = false;

    if (view != NULL)
    {
        main_window_close (&view->main);
        memset (view, 0, sizeof (gtk_view_t));
        status = true;
    }

    return status;
}