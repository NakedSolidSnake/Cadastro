#ifndef WEBSERVER_H_
#define WEBSERVER_H_

#include <stdbool.h>
#include <civetweb.h>

typedef struct 
{
    struct mg_context *mg_context;
    struct mg_callbacks mg_callbacks;
    char *port;
} webserver_t;

typedef struct 
{
    char *port;
} webserver_args_t;

bool webserver_init (webserver_t *webserver);
bool webserver_open (webserver_t *webserver, webserver_args_t *args);
bool webserver_run (webserver_t *webserver);
bool webserver_close (webserver_t *webserver);

#endif /* WEBSERVER_H_ */
