#ifndef PERSON_REPOSITORY_FACTORY_H_
#define PERSON_REPOSITORY_FACTORY_H_

#include <person_repository_base.h>

// typedef enum 
// {
//     person_repository_type_file,
//     person_repository_type_sqlite
// } person_repository_type_t;

person_repository_base_t person_repository_create (const char *type);

#endif /* PERSON_REPOSITORY_FACTORY_H_ */
