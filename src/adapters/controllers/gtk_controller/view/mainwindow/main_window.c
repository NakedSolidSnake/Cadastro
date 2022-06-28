#include "main_window.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>

static bool main_window_graphics_init (main_window_t *window);

bool main_window_init (main_window_t *window)
{
    bool status = false;

    if (window != NULL)
    {
        memset (window, 0, sizeof (main_window_t));
        
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

    window->widgets->window =          GTK_WIDGET (gtk_builder_get_object (builder, "window_main"));
    window->widgets->person_treeview = GTK_WIDGET (gtk_builder_get_object (builder, "person_treeview"));
    window->widgets->person_model =    GTK_WIDGET (gtk_builder_get_object (builder, "person_model"));
    window->widgets->txt_search =      GTK_WIDGET (gtk_builder_get_object (builder, "txt_search"));
    window->widgets->bt_insert =       GTK_WIDGET (gtk_builder_get_object (builder, "bt_insert"));
    window->widgets->bt_edit =         GTK_WIDGET (gtk_builder_get_object (builder, "bt_edit"));
    window->widgets->bt_delete =       GTK_WIDGET (gtk_builder_get_object (builder, "bt_delete"));

    gtk_builder_connect_signals (builder, window);

    g_object_unref (builder);

    return true;
}

void on_bt_insert_clicked (GtkButton *bt_insert, void *data)
{
    printf ("insert.\n");
    main_window_t *mw = (main_window_t *)data;

    insert_dialog_args_t args = 
    {
        .argc = mw->argc,
        .argv = mw->argv,
        .parent = mw->widgets->window
    };

    insert_dialog_open (&mw->insert, &args);
    insert_dialog_run (&mw->insert);
    insert_dialog_close (&mw->insert);
}

void on_bt_edit_clicked (GtkButton *bt_edit, void *data)
{
    printf ("edit.\n");
    main_window_t *mw = (main_window_t *)data;

    edit_dialog_args_t args = 
    {
        .argc = mw->argc,
        .argv = mw->argv,
        .parent = mw->widgets->window
    };

    edit_dialog_open (&mw->edit, &args);
    edit_dialog_run (&mw->edit);
    edit_dialog_close (&mw->edit);
}

void on_bt_delete_clicked (GtkButton *bt_insert, void *data)
{
    printf ("delete.\n");
}

void on_window_main_destroy (void)
{
    gtk_main_quit ();
}