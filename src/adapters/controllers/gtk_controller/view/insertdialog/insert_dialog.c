#include <gtk/gtk.h>
#include "insert_dialog.h"
#include <string.h>


static bool insert_dialog_graphics_init (insert_dialog_t *dialog);

bool insert_dialog_init (insert_dialog_t *dialog)
{
    bool status = false;

    if (dialog != NULL)
    {
        memset (dialog, 0, sizeof (insert_dialog_t));
        status = true;
    }

    return status;
}

bool insert_dialog_open (insert_dialog_t *dialog, insert_dialog_args_t *args)
{
    bool status = false;

    if (dialog != NULL && args != NULL)
    {
        dialog->con = args->con;
        status = insert_dialog_graphics_init (dialog);
    }

    return status;
}

bool insert_dialog_run (insert_dialog_t *dialog)
{
    bool status = false;

    if (dialog != NULL)
    {
        gtk_dialog_run (GTK_DIALOG (dialog->widgets->dialog));
        status = true;
    }

    return status;
}

bool insert_dialog_close (insert_dialog_t *dialog)
{
    bool status = false;

    if (dialog != NULL)
    {
        g_slice_free (insert_dialog_widgets_t, dialog->widgets);
        memset (dialog, 0, sizeof (insert_dialog_t));
        status = true;
    }

    return status;
}

static bool insert_dialog_graphics_init (insert_dialog_t *dialog)
{
    GtkBuilder *builder;

    dialog->widgets = g_slice_new (insert_dialog_widgets_t);

    builder = gtk_builder_new ();

    gtk_builder_add_from_file (builder, "resources/insert_window.glade", NULL);

    dialog->widgets->dialog      = GTK_WIDGET (gtk_builder_get_object (builder, "insert_window"));
    dialog->widgets->txt_name    = GTK_WIDGET (gtk_builder_get_object (builder, "txt_name"));
    dialog->widgets->txt_address = GTK_WIDGET (gtk_builder_get_object (builder, "txt_address"));
    dialog->widgets->txt_age     = GTK_WIDGET (gtk_builder_get_object (builder, "txt_age"));
    dialog->widgets->bt_confirm  = GTK_WIDGET (gtk_builder_get_object (builder, "bt_confirm"));
    dialog->widgets->bt_cancel   = GTK_WIDGET (gtk_builder_get_object (builder, "bt_cancel"));

    gtk_builder_connect_signals (builder, dialog);

    g_object_unref (builder);

    return true;
}

void on_insert_window_destroy (void)
{

}

void on_bt_insert_confirm_clicked (GtkButton *bt_insert, void *data)
{
    insert_dialog_t *d = (insert_dialog_t *)data;

    char *name = (char *)gtk_entry_get_text (d->widgets->txt_name);
    char *address = (char *)gtk_entry_get_text (d->widgets->txt_address);
    char *age = (char *)gtk_entry_get_text (d->widgets->txt_age);

    d->con->on_add (d->con->object, name, address, age);
    gtk_widget_destroy (GTK_WIDGET (d->widgets->dialog));
}

void on_bt_insert_cancel_clicked (GtkButton *bt_insert, void *data)
{
    insert_dialog_t *dialog = (insert_dialog_t *)data;
    gtk_widget_destroy (GTK_WIDGET (dialog->widgets->dialog));    
}