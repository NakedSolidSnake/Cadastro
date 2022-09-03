#ifndef CURL_REQUEST_H_
#define CURL_REQUEST_H_

#include <stdbool.h>
#include <deserializer.h>

typedef enum 
{
  curl_request_method_get,
  curl_request_method_post,
  curl_request_method_put,
  curl_request_method_delete  
} curl_request_method_t;

bool curl_request (const char *url, person_list_t *person_list, const char *data, curl_request_method_t method);

#endif /* CURL_REQUEST_H_ */
