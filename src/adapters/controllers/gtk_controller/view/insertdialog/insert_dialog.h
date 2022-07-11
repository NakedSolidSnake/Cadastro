#ifndef INSERT_DIALOG_H_
#define INSERT_DIALOG_H_

#include <stdbool.h>
#include <person_controller_events_base.h>

typedef struct 
{
    void *dialog;
    void *txt_name;
    void *txt_address;
    void *txt_age;
    void *bt_confirm;
    void *bt_cancel;
} insert_dialog_widgets_t;

typedef struct 
{
    void *parent;
    insert_dialog_widgets_t *widgets;
    person_controller_events_base_t *con;
} insert_dialog_t;


typedef struct 
{
    void *parent;
    int argc;
    char **argv;
    person_controller_events_base_t *con;
} insert_dialog_args_t;

bool insert_dialog_init (insert_dialog_t *dialog);
bool insert_dialog_open (insert_dialog_t *dialog, insert_dialog_args_t *args);
bool insert_dialog_run (insert_dialog_t *dialog);
bool insert_dialog_close (insert_dialog_t *dialog);

#endif /* INSERT_DIALOG_H_ */

