#ifndef PERSON_CONTROLLER_GTK_H_
#define PERSON_CONTROLLER_GTK_H_

#include <person_controller_base.h>
#include <person_service.h>
#include <gtk_view.h>

typedef struct 
{
    person_controller_base_t base;
    person_service_t *service;
    gtk_view_t view;
} person_controller_gtk_t;

bool person_controller_gtk_init (void *object);
bool person_controller_gtk_open (void *object, person_controller_args_t *args);
bool person_controller_gtk_run (void *object);
bool person_controller_gtk_close (void *object);

person_controller_base_t person_controller_gtk_create (person_controller_args_t *args);

#endif /* PERSON_CONTROLLER_GTK_H_ */
