#include "person_client_gtk.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <main_window.h>
#include <deserializer.h>
#include <serializer.h>
#include <curl/curl.h>
#include <curl_request.h>

#define PERSON_CLIENT_BUFFER_SEARCH 1024

static void person_client_events_on_get(void *object);
static void person_client_events_on_add(void *object, char *name, char *address, char *age);
static void person_client_events_on_update(void *object, int id, char *name, char *address, char *age);
static void person_client_events_on_delete(void *object, int id);
static void person_client_events_on_search(void *object, const char *name);

static main_window_t main_window;

bool person_client_gtk_init(person_client_gtk_t *client)
{
    bool status = false;

    if (client != NULL)
    {

        client->events.object = client;
        client->events.on_get = person_client_events_on_get;
        client->events.on_add = person_client_events_on_add;
        client->events.on_update = person_client_events_on_update;
        client->events.on_search = person_client_events_on_search;
        client->events.on_delete = person_client_events_on_delete;

        status = main_window_init(&main_window);

        client->view = &main_window.base;
    }

    return status;
}

bool person_client_gtk_open(person_client_gtk_t *client, person_client_args_t *args)
{
    bool status = false;
    main_window_args_t main_window_args;

    if (client != NULL && args != NULL)
    {
        snprintf (client->url, PERSON_CLIENT_GTK_URL_SIZE, "%s:%s%s", args->host, args->port, args->endpoint);
        
        main_window_args.argc = args->argc;
        main_window_args.argv = args->argv;
        main_window_args.con = &client->events;
        status = main_window_open(&main_window, &main_window_args);
    }

    return status;
}

bool person_client_gtk_run(person_client_gtk_t *client)
{
    bool status = false;

    if (client != NULL)
    {
        status = main_window_run(&main_window);
    }

    return status;
}

bool person_client_gtk_close(person_client_gtk_t *client)
{
    bool status = false;

    if (client != NULL)
    {
        main_window_close(&main_window);

        memset(client, 0, sizeof(person_client_gtk_t));
        status = true;
    }

    return status;
}

static void person_client_events_on_get(void *object)
{
    person_client_gtk_t *client = (person_client_gtk_t *)object;
    person_list_t person_list;

    curl_request (client->url, &person_list, NULL, curl_request_method_get);
    
    client->view->set_all_persons(client->view->object, person_list.array, array_list_get_size (person_list.array));

    array_list_destroy (person_list.array);
}

static void person_client_events_on_add(void *object, char *name, char *address, char *age)
{
    person_client_gtk_t *client = (person_client_gtk_t *)object;

    person_t person = person_create(name, address, atoi(age));

    char *json_string = serialize_person (&person);

    curl_request (client->url, NULL, json_string, curl_request_method_post);
    
    free (json_string);
}

static void person_client_events_on_update(void *object, int id, char *name, char *address, char *age)
{
    person_client_gtk_t *client = (person_client_gtk_t *)object;
    char url [1024] = {0};

    person_t person = person_create(name, address, atoi(age));

    char *json_string = serialize_person (&person);

    snprintf (url, 1024, "%s?id=%d", client->url, id);

    curl_request (url, NULL, json_string, curl_request_method_put);
    
    free (json_string);
}

static void person_client_events_on_delete(void *object, int id)
{
    person_client_gtk_t *client = (person_client_gtk_t *)object;
    char url [1024] = {0};

    snprintf (url, 1024, "%s?id=%d", client->url, id);

    curl_request (url, NULL, NULL, curl_request_method_delete);
}

static void person_client_events_on_search(void *object, const char *name)
{
    char buffer[PERSON_CLIENT_BUFFER_SEARCH] = {0};
    message_type_t type = message_info;
    dialog_button_t button_type = dialog_button_ok;
    person_client_gtk_t *client = (person_client_gtk_t *)object;
    char *message_found_str = "FOUND! - [ID: %d, NAME: %s, ADDRESS: %s, AGE: %d]";
    char *message_error_str = "Item not found";
    bool status = false;
    person_t p;
    strncpy(p.name, name, PERSON_NAME_LEN);

    // bool status = con->service->repository->find(con->service->repository->client, &p);

    if (status == true)
    {
        snprintf(buffer, PERSON_CLIENT_BUFFER_SEARCH, message_found_str, p.id, p.name, p.address, p.age);
    }
    else
    {
        type = message_error;
        snprintf(buffer, PERSON_CLIENT_BUFFER_SEARCH, "%s", message_error_str);
    }

    // con->view->show_dialog_message(con->view->client, buffer, type, button_type);
}