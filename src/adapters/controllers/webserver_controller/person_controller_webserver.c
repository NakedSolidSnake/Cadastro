#include <person_controller_webserver.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

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

        webserver_args_t web_args = 
        {
            .port = "9090"
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
