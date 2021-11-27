#ifndef APPLICATION_H_
#define APPLICATION_H_

#include <stdbool.h>
#include <repository.h>
#include <view_base.h>

typedef struct 
{
    view_base *view;
    repository_base *repository;
} application_t;

bool application_init(application_t *app, view_base *view, repository_base *repository);
bool application_run(application_t *app);

#endif /* APPLICATION_H_ */
