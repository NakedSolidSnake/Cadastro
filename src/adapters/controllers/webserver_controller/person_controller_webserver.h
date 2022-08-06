#ifndef PERSON_CONTROLLER_WEBSERVER_H_
#define PERSON_CONTROLLER_WEBSERVER_H_

#include <person_controller_base.h>
#include <person_service.h>
#include <webserver/webserver.h>

typedef struct 
{
    person_controller_base_t base;
    person_service_t *service;
    webserver_t server;
    handle_list_t *list;
} person_controller_webserver_t;

bool person_controller_webserver_init (void *object);
bool person_controller_webserver_open (void *object, person_controller_args_t *args);
bool person_controller_webserver_run (void *object);
bool person_controller_webserver_close (void *object);

person_controller_base_t person_controller_webserver_create (person_controller_args_t *args);


#endif /* PERSON_CONTROLLER_WEBSERVER_H_ */
