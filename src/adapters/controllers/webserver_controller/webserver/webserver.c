#include "webserver.h"
#include <string.h>
#include <cJSON.h>
#include <unistd.h>

static int log_message (const struct mg_connection *conn, const char *message);
static bool webserver_handle_register (webserver_t *webserver);

bool webserver_init (webserver_t *webserver)
{
    bool status = false;

    if (webserver != NULL)
    {
        memset (webserver, 0, sizeof (webserver_t));
        mg_init_library (MG_FEATURES_DEFAULT);

        webserver->mg_callbacks.log_message = log_message;
        status = true;
    }

    return status;
}

bool webserver_open (webserver_t *webserver, webserver_args_t *args)
{
    bool status = false;

    if (webserver != NULL && args != NULL && args->list != NULL && args->list->amount > 0)
    {
        webserver->port = args->port;
        webserver->list = args->list;

        status = true;
    }

    return status;
}

bool webserver_run (webserver_t *webserver)
{
    bool status = false;

    if (webserver != NULL)
    {
        const char *options[]  =
        {
            "listening_ports",
            webserver->port,
            "request_timeout_ms",
            "10000",
            "error_log_file",
            "error.log",
            "enable_auth_domain_check",
            "no",
            "document_root",
            "./assets",
            0
        };

        webserver->mg_context = mg_start (&webserver->mg_callbacks, 0, options);

        if (webserver->mg_context != NULL)
        {
            status = webserver_handle_register (webserver);
            
            while (status)
                usleep (1);
        }
        
    }

    return status;
}

bool webserver_close (webserver_t *webserver)
{
    bool status = false;

    if (webserver != NULL)
    {
        mg_stop (webserver->mg_context);
        memset (webserver, 0, sizeof (webserver_t));
        status = true;
    }

    return status;
}

static int log_message (const struct mg_connection *conn, const char *message)
{
    return 1;
}

static bool webserver_handle_register (webserver_t *webserver)
{
    bool status = false;

    for (unsigned char i = 0; i < webserver->list->amount; i ++)
    {
        handle_t *h = &webserver->list->handles[i];
        mg_set_request_handler (webserver->mg_context,
                                h->endpoint,
                                h->handler,
                                h->data);
    }

    status = true;

    return status;
}
