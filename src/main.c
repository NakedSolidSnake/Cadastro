#include <person_service.h>
#include <person_repository_factory.h>
#include <person_controller_factory.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    person_repository_base_t repository = person_repository_create (person_repository_type_sqlite);

    person_service_t service;
    person_service_init (&service);
    person_service_open (&service, (person_repository_base_t *)&repository);

    person_controller_args_t args = 
    {
        .argc = argc,
        .argv = argv,
        .service = &service
    };

    person_controller_base_t controller = person_controller_factory_create (person_controller_type_cli, &args);
    controller.run (controller.object);

    controller.close (controller.object);
    person_service_close (&service);
    
    return EXIT_SUCCESS;
}
