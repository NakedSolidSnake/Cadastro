#include "person_controller_gtk.h"
#include <string.h>
#include <stdlib.h>

bool person_controller_gtk_init (void *object)
{
    bool status = false;

    if (object != NULL)
    {
        person_controller_gtk_t *gtk_controller = (person_controller_gtk_t *)object;

        gtk_controller->base.object = gtk_controller;
        gtk_controller->base.init   = person_controller_gtk_init;
        gtk_controller->base.open   = person_controller_gtk_open;
        gtk_controller->base.run    = person_controller_gtk_run;
        gtk_controller->base.close  = person_controller_gtk_close;

        status = gtk_view_init (&gtk_controller->view);
    }

    return status;
}

bool person_controller_gtk_open (void *object, person_controller_args_t *args)
{
    bool status = false;
    gtk_view_args_t gtk_view_args;

    if (object != NULL && args != NULL && args->service != NULL)
    {
        person_controller_gtk_t *gtk_controller = (person_controller_gtk_t *)object;
        gtk_controller->service = args->service;

        gtk_view_args.argc = args->argc;
        gtk_view_args.argv = args->argv;
        status = gtk_view_open (&gtk_controller->view, &gtk_view_args);
    }

    return status;
}

bool person_controller_gtk_run (void *object)
{
    bool status = false;

    if (object != NULL)
    {
        person_controller_gtk_t *gtk_controller = (person_controller_gtk_t *)object;

        status = gtk_view_run (&gtk_controller->view);
    }

    return status;
}

bool person_controller_gtk_close (void *object)
{
    bool status = false;

    if (object != NULL)
    {
        person_controller_gtk_t *gtk_controller = (person_controller_gtk_t *)object;

        gtk_view_close (&gtk_controller->view);

        memset (gtk_controller, 0, sizeof (person_controller_gtk_t));
        status = true;
    }

    return status;
}

person_controller_base_t person_controller_gtk_create (person_controller_args_t *args)
{
    static person_controller_gtk_t gtk_controller;

    person_controller_gtk_init (&gtk_controller);
    person_controller_gtk_open (&gtk_controller, args);

    return gtk_controller.base;
}