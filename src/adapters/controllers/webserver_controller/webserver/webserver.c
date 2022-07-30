#include "webserver.h"
#include <string.h>

static int log_message (const struct mg_connection *conn, const char *message);

static int handler_index (struct mg_connection *conn, void *data);


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

    if (webserver != NULL && args != NULL)
    {
        webserver->port = args->port;

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
            mg_set_request_handler (webserver->mg_context, "/", handler_index, 0);
            status = true;
            while (true);
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

static int handler_index (struct mg_connection *conn, void *data)
{
    char path [1024] = {0};

    const struct mg_request_info *ri = mg_get_request_info (conn);

    const char *root = mg_get_option (mg_get_context (conn), "document_root");

    strncpy (path, root, sizeof (path));

    if (strcmp (ri->local_uri, "/") == 0)
    {
        strncat (path, "/index.html", sizeof (path) - strlen (root));
    }
    else 
    {
        strncat (path, ri->local_uri, sizeof (path) - strlen (root));
    }

    mg_send_file (conn, path);

    return 200;
}