#ifndef HANDLERS_H_
#define HANDLERS_H_

#include <civetweb.h>
#include <cJSON.h>

int handler_index (struct mg_connection *conn, void *data);
int handler_version_request (struct mg_connection *conn, void *data);
int send_json (struct mg_connection *conn, cJSON *json_obj);

#endif /* HANDLERS_H_ */
