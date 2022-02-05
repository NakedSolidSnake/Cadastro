#ifndef PERSON_CONTROLLER_CLI_H_
#define PERSON_CONTROLLER_CLI_H_

#include <person_controller_base.h>
#include <person_service.h>
#include <cli/cli.h>

typedef struct 
{
    person_controller_base_t base;
    person_service_t *service;
    cli_t cli;
} person_controller_cli_t;

bool person_controller_cli_init (void *object);
bool person_controller_cli_open (void *object, person_service_t *service);
bool person_controller_cli_run (void *object);
bool person_controller_cli_close (void *object);

person_controller_base_t person_controller_cli_create (person_service_t *service);

#endif /* PERSON_CONTROLLER_CLI_H_ */
