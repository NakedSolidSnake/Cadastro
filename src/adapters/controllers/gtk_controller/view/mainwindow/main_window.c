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
        status = true;
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

    window->widgets->window = GTK_WIDGET (gtk_builder_get_object (builder, "window_main"));

    gtk_builder_connect_signals (builder, window);

    g_object_unref (builder);

    return true;
}