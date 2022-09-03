#ifndef EDIT_DIALOG_H_
#define EDIT_DIALOG_H_

#include <stdbool.h>
#include <person_client_events_base.h>

typedef struct 
{
    void *dialog;
    void *txt_name;
    void *txt_address;
    void *txt_age;
    void *bt_confirm;
    void *bt_cancel;
} edit_dialog_widgets_t;

typedef struct 
{
    void *parent;
    edit_dialog_widgets_t *widgets;
    person_client_events_base_t *con;
    int id;
    char *name;
    char *address;
    int age;
} edit_dialog_t;


typedef struct 
{
    void *parent;
    int argc;
    char **argv;
    person_client_events_base_t *con;
    int id;
    char *name;
    char *address;
    int age;
} edit_dialog_args_t;

bool edit_dialog_init (edit_dialog_t *dialog);
bool edit_dialog_open (edit_dialog_t *dialog, edit_dialog_args_t *args);
bool edit_dialog_run (edit_dialog_t *dialog);
bool edit_dialog_close (edit_dialog_t *dialog);

#endif /* EDIT_DIALOG_H_ */
