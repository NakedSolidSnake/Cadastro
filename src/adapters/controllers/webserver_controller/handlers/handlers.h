#ifndef HANDLERS_H_
#define HANDLERS_H_

#include <civetweb.h>
#include <cJSON.h>
#include <person_controller_webserver.h>

#define HANDLER_REQUEST_AMOUNT  5

#define HANDLER_REQUEST_GET     "GET"
#define HANDLER_REQUEST_POST    "POST"
#define HANDLER_REQUEST_PUT     "PUT"
#define HANDLER_REQUEST_DELETE  "DELETE"

#define HANDLER_ENDPOINT_PERSON     "/persons"
#define HANDLER_ENDPOINT_VERSION    "/version"
#define HANDLER_REQUEST_INDEX       "/"

typedef enum 
{
    http_continue = 100,
    http_switching_protocols = 101,
    http_early_hints = 103,
    http_ok = 200,
    http_created = 201,
    http_accepted = 202,
    http_non_authoritative_information = 203,
    http_no_content = 204,
    http_reset_content = 205,
    http_partial_content = 206,
    http_multiple_choices = 300,
    http_moved_permanently = 301,
    http_found = 302,
    http_see_other = 303,
    http_not_modified = 304,
    http_temporary_redirect = 307,
    http_permanent_redirect = 308,
    http_bad_request = 400,
    http_unauthorized = 401,
    http_payment_required = 402,
    http_forbidden = 403,
    http_not_found = 404,
    http_method_not_allowed = 405,
    http_not_acceptable = 406,
    http_proxy_authentication_required = 407,
    http_request_timeout = 408,
    http_conflict = 409,
    http_gone = 410,
    http_length_required = 411,
    http_precondition_failed = 412,
    http_payload_too_large = 413,
    http_uri_too_long = 414,
    http_unsupported_media_type = 415,
    http_range_not_satisfiable = 416,
    http_expectation_failed = 417,
    http_im_a_teapot = 418,
    http_unprocessable_entity = 422,
    http_too_early = 425,
    http_upgrade_required = 426,
    http_precondition_required = 428,
    http_too_many_requests = 429,
    http_request_header_fields_too_large = 431,
    http_unavailable_for_legal_reasons = 451,
    http_internal_server_error = 500,
    http_not_implemented = 501,
    http_bad_gateway = 502,
    http_service_unavailable = 503,
    http_gateway_timeout = 504,
    http_http_version_not_supported = 505,
    http_variant_also_negotiates = 506,
    http_insufficient_storage = 507,
    http_loop_detected = 508,
    http_not_extended = 510,
    http_network_authentication_required = 511
} http_status_t;


typedef int (*handler_request_t) (struct mg_connection *conn, void *data);

typedef struct 
{
    const char *method;
    handler_request_t handler;
} handler_request_map_t;

typedef struct 
{
    handler_request_map_t requests[HANDLER_REQUEST_AMOUNT];
    unsigned char amount;
} handler_requests_map_t;

int handler_requests (struct mg_connection *conn, void *data);
int handler_get (struct mg_connection *conn, void *data);
int handler_post (struct mg_connection *conn, void *data);
int handler_delete (struct mg_connection *conn, void *data);
int handler_put (struct mg_connection *conn, void *data);
int handler_index (struct mg_connection *conn, void *data);
int handler_version_request (struct mg_connection *conn, void *data);
int send_json (struct mg_connection *conn, cJSON *json_obj, http_status_t status);

cJSON *serialize_person_list (person_t *list, unsigned int amount);
cJSON *serialize_person (cJSON *obj, person_t *person);
cJSON *serialize_error (const char *error, const char *hint);

bool deserialize_person (const char *buffer, person_t *person);

#endif /* HANDLERS_H_ */
