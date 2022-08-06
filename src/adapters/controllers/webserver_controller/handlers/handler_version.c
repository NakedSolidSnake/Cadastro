#include "handlers.h"
#include <string.h>
#include <stdlib.h>

int handler_version_request (struct mg_connection *conn, void *data)
{
   cJSON *obj = cJSON_CreateObject ();

   if (!obj) 
   {
        mg_send_http_error (conn, http_internal_server_error, "Server Error");
        return http_internal_server_error;
   }

   cJSON_AddStringToObject (obj, "version", CIVETWEB_VERSION);
   send_json (conn, obj, http_ok);

   cJSON_Delete (obj);

   return http_ok;
}