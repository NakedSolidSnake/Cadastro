#include "handlers.h"
#include <string.h>
#include <stdlib.h>

static cJSON *handler_add (void *object, char *buffer, int size);

int handler_post (struct mg_connection *conn, void *data)
{
   int status;
   char buffer [1024];
   cJSON *json;

   int size = mg_read (conn, buffer, sizeof (buffer) - 1);
   buffer[size] = 0;

   json = handler_add (data, buffer, size);

   if (json != NULL)
      status = http_accepted;

   else 
   {
      json = serialize_error ("Not modified", "Content not created");
      status = http_not_modified;
   }

   send_json (conn, json, status);

   return status;
}

static cJSON *handler_add (void *object, char *buffer, int size)
{
   person_t person;
   cJSON *json = NULL;

   person_controller_webserver_t *controller = (person_controller_webserver_t *)object;

   if (deserialize_person (buffer, &person) == true)
   {
      if (controller->service->base.add (controller->service->base.object, &person) == true)
         json = serialize_error ("Created", "Registry created");
   }

   return json;
}