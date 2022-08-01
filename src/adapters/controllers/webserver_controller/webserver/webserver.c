#include "webserver.h"
#include <string.h>
#include <cJSON.h>

static int log_message (const struct mg_connection *conn, const char *message);

static int handler_index (struct mg_connection *conn, void *data);
static int handler_version_request (struct mg_connection *conn, void *data);
static int send_json (struct mg_connection *conn, cJSON *json_obj);

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
            mg_set_request_handler (webserver->mg_context, "/version", handler_version_request, 0);
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

static int handler_version_request (struct mg_connection *conn, void *data)
{
   cJSON *obj = cJSON_CreateObject ();

   if (!obj) 
   {
        mg_send_http_error (conn, 500, "Server Error");
        return 500;
   }

   cJSON_AddStringToObject (obj, "version", CIVETWEB_VERSION);
   send_json (conn, obj);

   cJSON_Delete (obj);

   return 200;
}

static int send_json (struct mg_connection *conn, cJSON *json_obj)
{
    char *json_string = cJSON_PrintUnformatted (json_obj);
    size_t json_str_len = strlen (json_string);

    mg_send_http_ok (conn, "application/json; charset=utf-8", json_str_len);

    mg_write (conn, json_string, json_str_len);

    cJSON_free (json_string);

    return (int) json_str_len;
}