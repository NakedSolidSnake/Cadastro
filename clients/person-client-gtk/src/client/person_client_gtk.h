#ifndef PERSON_CLIENT_GTK_H_
#define PERSON_CLIENT_GTK_H_

#include <stdbool.h>
#include <person_client_events_base.h>
#include <view_base.h>

#define PERSON_CLIENT_GTK_URL_SIZE  200

typedef struct 
{
    person_client_events_base_t events;
    view_base_t *view;
    char url [PERSON_CLIENT_GTK_URL_SIZE];
} person_client_gtk_t;

typedef struct 
{
    int argc;
    char **argv;
    char *host;
    char *port;
    char *endpoint;
} person_client_args_t;

bool person_client_gtk_init (person_client_gtk_t *client);
bool person_client_gtk_open (person_client_gtk_t *client, person_client_args_t *args);
bool person_client_gtk_run (person_client_gtk_t *client);
bool person_client_gtk_close (person_client_gtk_t *client);

#endif /* PERSON_CLIENT_GTK_H_ */
