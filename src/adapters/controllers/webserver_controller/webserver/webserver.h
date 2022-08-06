#ifndef WEBSERVER_H_
#define WEBSERVER_H_

#include <stdbool.h>
#include <civetweb.h>

#define WEBSERVER_HANDLER_AMOUNT    10

typedef int (*handler_t) (struct mg_connection *conn, void *data);

typedef struct 
{
    const char *endpoint;
    handler_t handler;
    void *data;
} handle_t;

typedef struct 
{
    handle_t handles [WEBSERVER_HANDLER_AMOUNT];
    unsigned char amount;
} handle_list_t;

typedef struct 
{
    struct mg_context *mg_context;
    struct mg_callbacks mg_callbacks;
    char *port;
    handle_list_t *list;
} webserver_t;

typedef struct 
{
    handle_list_t *list;
    char *port;
} webserver_args_t;

bool webserver_init (webserver_t *webserver);
bool webserver_open (webserver_t *webserver, webserver_args_t *args);
bool webserver_run (webserver_t *webserver);
bool webserver_close (webserver_t *webserver);

#endif /* WEBSERVER_H_ */
