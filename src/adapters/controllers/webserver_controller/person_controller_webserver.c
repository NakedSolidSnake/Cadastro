#include <person_controller_webserver.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <handlers.h>

static handle_list_t *person_controller_webserver_get_handle_list (person_controller_webserver_t *webserver_controller);

bool person_controller_webserver_init (void *object)
{
    bool status = false;

    if (object != NULL)
    {
        person_controller_webserver_t *webserver_controller = (person_controller_webserver_t *)object;

        memset (webserver_controller, 0, sizeof (person_controller_webserver_t));

        webserver_controller->base.object = webserver_controller;

        webserver_controller->base.init  = person_controller_webserver_init;
        webserver_controller->base.open  = person_controller_webserver_open;
        webserver_controller->base.run   = person_controller_webserver_run;
        webserver_controller->base.close = person_controller_webserver_close;

        status = webserver_init (&webserver_controller->server);
    }

    return status;
}

bool person_controller_webserver_open (void *object, person_controller_args_t *args)
{
    bool status = false;

    if (object != NULL && args != NULL)
    {
        person_controller_webserver_t *webserver_controller = (person_controller_webserver_t *)object;

        webserver_controller->service = args->service;
        webserver_controller->list = person_controller_webserver_get_handle_list (webserver_controller);

        webserver_args_t web_args = 
        {
            .port = args->port,
            .list = webserver_controller->list
        };

        status = webserver_open (&webserver_controller->server, &web_args);
    }

    return status;
}

bool person_controller_webserver_run (void *object)
{
    person_controller_webserver_t *webserver_controller = (person_controller_webserver_t *)object;
    webserver_run (&webserver_controller->server);
    return true;
}

bool person_controller_webserver_close (void *object)
{
    bool status = false;

    if (object != NULL)
    {
        person_controller_webserver_t *webserver_controller = (person_controller_webserver_t *)object;

        webserver_close (&webserver_controller->server);

        free (webserver_controller->list);

        memset (webserver_controller, 0, sizeof (person_controller_webserver_t));
        status = true;
    }

    return status;
}

person_controller_base_t person_controller_webserver_create (person_controller_args_t *args)
{
    static person_controller_webserver_t webserver_controller;

    person_controller_webserver_init (&webserver_controller);
    person_controller_webserver_open (&webserver_controller, args);

    return webserver_controller.base;
}

static handle_list_t *person_controller_webserver_get_handle_list (person_controller_webserver_t *webserver_controller)
{
    handle_list_t *list = (handle_list_t*) calloc (1, sizeof (handle_list_t));

    list->handles[0].endpoint = HANDLER_REQUEST_INDEX;
    list->handles[0].handler = handler_index;
    list->handles[0].data = webserver_controller;

    list->handles[1].endpoint = HANDLER_ENDPOINT_VERSION;
    list->handles[1].handler = handler_version_request;
    list->handles[1].data = webserver_controller;

    list->handles[2].endpoint = HANDLER_ENDPOINT_PERSON;
    list->handles[2].handler = handler_requests;
    list->handles[2].data = webserver_controller;

    list->amount = 3;

    return list;
}