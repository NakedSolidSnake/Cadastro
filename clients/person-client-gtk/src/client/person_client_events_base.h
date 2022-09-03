#ifndef PERSON_CLIENT_EVENTS_BASE_H_
#define PERSON_CLIENT_EVENTS_BASE_H_

typedef struct 
{
    void *object;
    void (*on_get) (void *object);
    void (*on_add) (void *object, char *name, char *address, char *age);
    void (*on_update) (void *object, int id, char *name, char *address, char *age);
    void (*on_delete) (void *object, int id);
    void (*on_search) (void *object, const char *name);
} person_client_events_base_t;

#endif /* PERSON_CLIENT_EVENTS_BASE_H_ */
