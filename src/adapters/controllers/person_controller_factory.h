#ifndef PERSON_CONTROLLER_FACTORY_H_
#define PERSON_CONTROLLER_FACTORY_H_

#include <person_controller_base.h>

typedef enum 
{
    person_controller_type_cli,
    // person_controller_type_gtk,
    // person_controller_type_webserver
} person_controller_type_t;

person_controller_base_t person_controller_factory_create (person_controller_type_t type, person_service_t *service);

#endif /* PERSON_CONTROLLER_FACTORY_H_ */
