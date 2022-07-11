#ifndef MAIN_WINDOW_H_
#define MAIN_WINDOW_H_

#include <stdbool.h>
#include <insert_dialog.h>
#include <edit_dialog.h>
#include <view_base.h>
#include <person_controller_events_base.h>

typedef struct 
{
    void *window;
    void *txt_search;
    void *person_model;
    void *person_treeview;
    void *bt_insert;
    void *bt_edit;
    void *bt_delete;
    void *bt_find;
} main_window_widgets_t;

typedef struct 
{
    view_base_t base;
    main_window_widgets_t *widgets;
    insert_dialog_t insert;
    edit_dialog_t edit;
    person_controller_events_base_t *con;
    int argc;
    char **argv;
} main_window_t;

typedef struct 
{
    int argc;
    char **argv;
    person_controller_events_base_t *con;
} main_window_args_t;

bool main_window_init (main_window_t *window);
bool main_window_open (main_window_t *window, main_window_args_t *args);
bool main_window_run (main_window_t *window);
bool main_window_close (main_window_t *window);

#endif /* MAIN_WINDOW_H_ */
