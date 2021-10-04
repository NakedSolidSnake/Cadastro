#ifndef USE_CASES_H
#define USE_CASES_H

#include <repository.h>

void use_case_person_add_new(repository_base *repository);
void use_case_person_update(repository_base *repository);
void use_case_person_list(repository_base *repository);
void use_case_person_find(repository_base *repository);
void use_case_person_delete(repository_base *repository);
void use_case_person_quit(repository_base *repository);
#endif /* USE_CASES_H */
