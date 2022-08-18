#ifndef PERSON_CONTROLLER_FACTORY_H_
#define PERSON_CONTROLLER_FACTORY_H_

#include <person_controller_base.h>

person_controller_base_t person_controller_factory_create (const char *type, person_controller_args_t *args);

#endif /* PERSON_CONTROLLER_FACTORY_H_ */
