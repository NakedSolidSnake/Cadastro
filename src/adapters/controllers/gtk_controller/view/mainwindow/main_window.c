#include "main_window.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>

typedef enum 
{
    Person_ID,
    Person_Name,
    Person_Address,
    Person_Age
} header_t;

static void main_window_set_all_persons (void *object, person_t *list, unsigned int amount);
static int  main_window_show_dialog_message (void *object, const char *message, message_type_t type, dialog_button_t button_type);
static bool main_window_graphics_init (main_window_t *window);
static GtkMessageType main_window_get_type (message_type_t type);
static void main_window_model_reload (main_window_t *mw);

bool main_window_init (main_window_t *window)
{
    bool status = false;

    if (window != NULL)
    {
        memset (window, 0, sizeof (main_window_t));

        window->base.object = window;
        window->base.set_all_persons = main_window_set_all_persons;
        window->base.show_dialog_message = main_window_show_dialog_message;
        
        if (insert_dialog_init (&window->insert) == true && 
            edit_dialog_init (&window->edit) == true)
        {
            status = true;
        }
    }

    return status;
}

bool main_window_open (main_window_t *window, main_window_args_t *args)
{
    bool status = false;

    if (window != NULL && args != NULL)
    {
        window->argc = args->argc;
        window->argv = args->argv;
        window->con  = args->con;

        status = main_window_graphics_init (window);
    }

    return status;
}

bool main_window_run (main_window_t *window)
{
    bool status = false;

    if (window != NULL)
    {
        gtk_widget_show (window->widgets->window);
        gtk_main ();
        status = true;
    }

    return status;
}

bool main_window_close (main_window_t *window)
{
    bool status = false;

    if (window != NULL)
    {
        g_slice_free (main_window_widgets_t, window->widgets);
        memset (window, 0, sizeof (main_window_t));
        status = true;
    }

    return status;
}

static bool main_window_graphics_init (main_window_t *window)
{
    GtkBuilder *builder;

    window->widgets = g_slice_new (main_window_widgets_t);

    gtk_init (&window->argc, &window->argv);

    builder = gtk_builder_new ();

    gtk_builder_add_from_file (builder, "resources/window.glade", NULL);

    window->widgets->window          = GTK_WIDGET (gtk_builder_get_object (builder, "window_main"));
    window->widgets->person_treeview = GTK_WIDGET (gtk_builder_get_object (builder, "person_treeview"));
    window->widgets->person_model    = GTK_WIDGET (gtk_builder_get_object (builder, "person_model"));
    window->widgets->txt_search      = GTK_WIDGET (gtk_builder_get_object (builder, "txt_search"));
    window->widgets->bt_insert       = GTK_WIDGET (gtk_builder_get_object (builder, "bt_insert"));
    window->widgets->bt_edit         = GTK_WIDGET (gtk_builder_get_object (builder, "bt_edit"));
    window->widgets->bt_delete       = GTK_WIDGET (gtk_builder_get_object (builder, "bt_delete"));
    window->widgets->bt_find         = GTK_WIDGET (gtk_builder_get_object (builder, "bt_find"));

    gtk_builder_connect_signals (builder, window);

    g_object_unref (builder);

    return true;
}

void on_bt_insert_clicked (GtkButton *bt_insert, void *data)
{
    main_window_t *mw = (main_window_t *)data;

    insert_dialog_args_t args = 
    {
        .argc = mw->argc,
        .argv = mw->argv,
        .parent = mw->widgets->window,
        .con = mw->con
    };

    insert_dialog_open (&mw->insert, &args);
    insert_dialog_run (&mw->insert);
    insert_dialog_close (&mw->insert);

    main_window_model_reload (mw);
}

void on_bt_edit_clicked (GtkButton *bt_edit, void *data)
{
    main_window_t *mw = (main_window_t *)data;

    GtkTreeSelection *selection;
    GtkTreeModel *model;
    GtkTreeIter iter;

    GValue value_id = {0,};
    GValue value_name = {0,};
    GValue value_address = {0,};
    GValue value_age = {0,};

    selection = gtk_tree_view_get_selection (mw->widgets->person_treeview);
    gboolean status = gtk_tree_selection_get_selected (selection, &model, &iter);

    if (status == TRUE)
    {
        gtk_tree_model_get_value (model, &iter, Person_ID, &value_id);
        int id = g_value_get_int (&value_id);

        gtk_tree_model_get_value (model, &iter, Person_Name, &value_name);
        char *name = (char *)g_value_get_string (&value_name);

        gtk_tree_model_get_value (model, &iter, Person_Address, &value_address);
        char *address = (char *)g_value_get_string (&value_address);

        gtk_tree_model_get_value (model, &iter, Person_Age, &value_age);
        int age = g_value_get_int (&value_age);

        edit_dialog_args_t args =
        {
            .argc = mw->argc,
            .argv = mw->argv,
            .parent = mw->widgets->window,
            .con = mw->con,
            .id = id,
            .name = name,
            .address = address,
            .age = age
        };

        edit_dialog_open(&mw->edit, &args);
        edit_dialog_run(&mw->edit);
        edit_dialog_close(&mw->edit);

        main_window_model_reload(mw);

        g_value_unset (&value_id);
        g_value_unset (&value_name);
        g_value_unset (&value_address);
        g_value_unset (&value_age);
    }
}

void on_bt_delete_clicked (GtkButton *bt_delete, void *data)
{
    main_window_t *mw = (main_window_t *)data;
    GtkTreeSelection *selection;
    GtkTreeModel *model;
    GtkTreeIter iter;

    GValue value = {0,};
    int id;

    selection = gtk_tree_view_get_selection (mw->widgets->person_treeview);
    gboolean status = gtk_tree_selection_get_selected (selection, &model, &iter);

    if (status == TRUE)
    {
        int answer = main_window_show_dialog_message (mw, "This register is about to be deleted. Are you sure?", message_question, dialog_button_ok_cancel);
        if (answer == GTK_RESPONSE_OK)
        {
            gtk_tree_model_get_value (model, &iter, Person_ID, &value);
            id = g_value_get_int (&value);
            mw->con->on_delete (mw->con->object, id);

            main_window_model_reload (mw);
        }        
    }

    g_value_unset (&value);
}

void on_bt_find_clicked (GtkButton *bt_find, void *data)
{
    main_window_t *mw = (main_window_t *)data;
    const char *text = (const char *)gtk_entry_get_text (GTK_ENTRY (mw->widgets->txt_search));

    mw->con->on_search (mw->con->object, text);
}

void on_window_main_destroy (void)
{
    gtk_main_quit ();
}

void on_window_main_show (GtkWidget *object, void *data)
{
    main_window_t *mw = (main_window_t *)data;
    main_window_model_reload (mw);
}

static void main_window_set_all_persons (void *object, person_t *list, unsigned int amount)
{
    main_window_t *mw = (main_window_t *)object;

    for (unsigned int i = 0; i < amount; i++)
    {
        GtkTreeIter iter;
        person_t *p = &list[i];

        gtk_list_store_append (GTK_LIST_STORE (mw->widgets->person_model), &iter);

        gtk_list_store_set (GTK_LIST_STORE (mw->widgets->person_model),
                            &iter,
                            Person_ID, p->id,
                            Person_Name, p->name,
                            Person_Address, p->address,
                            Person_Age, p->age,
                            -1);
    }
}

static int  main_window_show_dialog_message (void *object, const char *message, message_type_t type, dialog_button_t button_type)
{
    main_window_t *mw = (main_window_t *)object;
    int answer;

    GtkWidget *d = gtk_message_dialog_new (GTK_WINDOW (mw->widgets->window),
                                           GTK_DIALOG_MODAL,
                                           main_window_get_type (type),
                                           button_type, 
                                           "%s",
                                           message);

    answer = gtk_dialog_run (GTK_DIALOG (d));
    gtk_widget_destroy (d);
    return answer;
}

static GtkMessageType main_window_get_type (message_type_t type)
{
    GtkMessageType internal_type = GTK_MESSAGE_INFO;

    switch (type)
    {
    case message_info:
        internal_type = GTK_MESSAGE_INFO;
        break;
    case message_warning:
        internal_type = GTK_MESSAGE_WARNING;
        break;
    case message_question:
        internal_type = GTK_MESSAGE_QUESTION;
        break;
    case message_error:
        internal_type = GTK_MESSAGE_ERROR;
        break;
    
    default:
        break;
    }

    return internal_type;
}

static void main_window_model_reload (main_window_t *mw)
{
    gtk_list_store_clear (GTK_LIST_STORE (mw->widgets->person_model));
    mw->con->on_get (mw->con->object);
}
