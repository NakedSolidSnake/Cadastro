#include "person_controller_gtk.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <main_window.h>

#define PERSON_CONTROLLER_BUFFER_SEARCH  1024

static void person_controller_events_on_get (void *object);
static void person_controller_events_on_add (void *object, char *name, char *address, char *age);
static void person_controller_events_on_update (void *object, int id, char *name, char *address, char *age);
static void person_controller_events_on_delete (void *object, int id);
static void person_controller_events_on_search (void *object, const char *name);

static main_window_t main_window;

bool person_controller_gtk_init (void *object)
{
    bool status = false;

    if (object != NULL)
    {
        person_controller_gtk_t *c = (person_controller_gtk_t *)object;

        c->base.object = c;
        c->base.init   = person_controller_gtk_init;
        c->base.open   = person_controller_gtk_open;
        c->base.run    = person_controller_gtk_run;
        c->base.close  = person_controller_gtk_close;

        c->events.object = c;
        c->events.on_get = person_controller_events_on_get;
        c->events.on_add = person_controller_events_on_add;
        c->events.on_update = person_controller_events_on_update;
        c->events.on_search = person_controller_events_on_search;
        c->events.on_delete = person_controller_events_on_delete;

        status = main_window_init (&main_window);

        c->view = &main_window.base;
    }

    return status;
}

bool person_controller_gtk_open (void *object, person_controller_args_t *args)
{
    bool status = false;
    main_window_args_t main_window_args;

    if (object != NULL && args != NULL && args->service != NULL)
    {
        person_controller_gtk_t *gtk_controller = (person_controller_gtk_t *)object;
        gtk_controller->service = args->service;

        main_window_args.argc = args->argc;
        main_window_args.argv = args->argv;
        main_window_args.con  = &gtk_controller->events;
        status = main_window_open (&main_window, &main_window_args);
    }

    return status;
}

bool person_controller_gtk_run (void *object)
{
    bool status = false;

    if (object != NULL)
    {
        person_controller_gtk_t *gtk_controller = (person_controller_gtk_t *)object;
        (void)gtk_controller;
        status = main_window_run (&main_window);
    }

    return status;
}

bool person_controller_gtk_close (void *object)
{
    bool status = false;

    if (object != NULL)
    {
        person_controller_gtk_t *gtk_controller = (person_controller_gtk_t *)object;

        main_window_close (&main_window);

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

static void person_controller_events_on_get (void *object)
{
    person_controller_gtk_t *con = (person_controller_gtk_t *)object;
    person_t *list = NULL;
    unsigned int amount = 0;

    con->service->base.getall (con->service->base.object, &list, &amount);

    con->view->set_all_persons (con->view->object, list, amount);

    free (list);
}

static void person_controller_events_on_add (void *object, char *name, char *address, char *age)
{
    person_controller_gtk_t *con = (person_controller_gtk_t *)object;

    person_t p = person_create (name, address, atoi (age));

    con->service->repository->add (con->service->repository->object, &p);
}

static void person_controller_events_on_update (void *object, int id, char *name, char *address, char *age)
{
    person_controller_gtk_t *con = (person_controller_gtk_t *)object;
    person_t p = person_create (name, address, atoi (age));
    p.id = id;

    con->service->repository->update (con->service->repository->object, &p);
}   

static void person_controller_events_on_delete (void *object, int id)
{
    person_controller_gtk_t *con = (person_controller_gtk_t *)object;

    person_t p = {.id = id};

    con->service->repository->remove (con->service->repository->object, &p);
}

static void person_controller_events_on_search (void *object, const char *name)
{    
    char buffer [PERSON_CONTROLLER_BUFFER_SEARCH] = {0};
    message_type_t type = message_info;
    dialog_button_t button_type = dialog_button_ok;
    person_controller_gtk_t *con = (person_controller_gtk_t *)object;
    char *message_found_str = "FOUND! - [ID: %d, NAME: %s, ADDRESS: %s, AGE: %d]";
    char *message_error_str = "Item not found";

    person_t p;
    strncpy (p.name, name, PERSON_NAME_LEN);

    bool status = con->service->repository->find (con->service->repository->object, &p);

    if (status == true)
    {
        snprintf (buffer, PERSON_CONTROLLER_BUFFER_SEARCH, message_found_str, p.id, p.name, p.address, p.age);
    }
    else 
    {
        type = message_error;
        snprintf (buffer, PERSON_CONTROLLER_BUFFER_SEARCH, "%s", message_error_str);
    }

    con->view->show_dialog_message (con->view->object, buffer, type, button_type);

}