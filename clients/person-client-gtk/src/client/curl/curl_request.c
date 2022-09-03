#include "curl_request.h"
#include <curl/curl.h>

#define CURL_REQUEST_CUSTOM_METHOD_PUT      "PUT"
#define CURL_REQUEST_CUSTOM_METHOD_DELETE   "DELETE"

static size_t curl_request_get_callback (char *dest, size_t size, size_t nmemb, void *data)
{
    person_list_t *list = (person_list_t *)data;
    deserialize_person_list (list, dest);
    return 0;
}

static void curl_request_method_setup (CURL *curl, person_list_t *person_list, const char *data, curl_request_method_t method);
static void curl_request_get_setup (CURL *curl, person_list_t *person_list);
static void curl_request_post_setup (CURL *curl, const char *data);
static void curl_request_put_setup (CURL *curl, const char *data);
static void curl_request_delete_setup (CURL *curl);

bool curl_request (const char *url, person_list_t *person_list, const char *data, curl_request_method_t method)
{
    bool status = false;
    CURL *curl;
    CURLcode res;    

    curl = curl_easy_init ();
    if (curl != NULL)
    {
        curl_easy_setopt (curl, CURLOPT_URL, url);
        curl_request_method_setup (curl, person_list, data, method);

        res = curl_easy_perform (curl);

        if (res == CURLE_OK) 
            status = true;

        curl_easy_cleanup (curl);
    }

    curl_global_cleanup ();
    return status;
}

static void curl_request_method_setup (CURL *curl, person_list_t *person_list, const char *data, curl_request_method_t method)
{
    switch (method)
    {
    case curl_request_method_get:
        curl_request_get_setup (curl, person_list);
        break;

    case curl_request_method_post:
        curl_request_post_setup (curl, data);
        break;

    case curl_request_method_put:
        curl_request_put_setup (curl, data);
        break;

    case curl_request_method_delete:
        curl_request_delete_setup (curl);
        break;
    
    default:
        break;
    }
}

static void curl_request_get_setup (CURL *curl, person_list_t *person_list)
{
    curl_easy_setopt (curl, CURLOPT_WRITEFUNCTION, curl_request_get_callback);
    curl_easy_setopt (curl, CURLOPT_WRITEDATA, person_list);
}

static void curl_request_post_setup (CURL *curl, const char *data)
{
    curl_easy_setopt (curl, CURLOPT_POSTFIELDS, data);
    curl_easy_setopt (curl, CURLOPT_POSTFIELDSIZE, -1L);
}

static void curl_request_put_setup (CURL *curl, const char *data)
{
    curl_easy_setopt (curl, CURLOPT_POSTFIELDS, data);
    curl_easy_setopt (curl, CURLOPT_CUSTOMREQUEST, CURL_REQUEST_CUSTOM_METHOD_PUT);
}

static void curl_request_delete_setup (CURL *curl)
{
    curl_easy_setopt (curl, CURLOPT_CUSTOMREQUEST, CURL_REQUEST_CUSTOM_METHOD_DELETE);
}