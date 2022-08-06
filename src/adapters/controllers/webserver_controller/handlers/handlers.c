#include "handlers.h"
#include <string.h>
#include <stdlib.h>

int handler_index (struct mg_connection *conn, void *data)
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

int handler_version_request (struct mg_connection *conn, void *data)
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

int send_json (struct mg_connection *conn, cJSON *json_obj)
{
    char *json_string = cJSON_PrintUnformatted (json_obj);
    size_t json_str_len = strlen (json_string);

    mg_send_http_ok (conn, "application/json; charset=utf-8", json_str_len);

    mg_write (conn, json_string, json_str_len);

    cJSON_free (json_string);

    return (int) json_str_len;
}