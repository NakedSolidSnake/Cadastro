#include <person_service.h>
#include <person_repository_factory.h>
#include <person_controller_factory.h>
#include <stdlib.h>
#include <configuration.h>

int main(int argc, char *argv[])
{
    configuration_t conf;

    configuration_init (&conf);

    if (configuration_load (&conf) == false)
    {
        return EXIT_FAILURE;
    }

    person_repository_base_t repository = person_repository_create (conf.repository_type);

    person_service_t service;
    person_service_init (&service);
    person_service_open (&service, (person_repository_base_t *)&repository);

    person_controller_args_t args = 
    {
        .argc = argc,
        .argv = argv,
        .service = &service,
        .port = conf.webserver.port
    };

    person_controller_base_t controller = person_controller_factory_create (conf.controller_type, &args);
    controller.run (controller.object);

    controller.close (controller.object);
    person_service_close (&service);
    
    return EXIT_SUCCESS;
}
