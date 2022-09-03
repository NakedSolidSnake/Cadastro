#include <gtk/gtk.h>
#include "edit_dialog.h"
#include <string.h>


static bool edit_dialog_graphics_init (edit_dialog_t *dialog);

bool edit_dialog_init (edit_dialog_t *dialog)
{
    bool status = false;

    if (dialog != NULL)
    {
        memset (dialog, 0, sizeof (edit_dialog_t));
        status = true;
    }

    return status;
}

bool edit_dialog_open (edit_dialog_t *dialog, edit_dialog_args_t *args)
{
    bool status = false;

    if (dialog != NULL && args != NULL)
    {
        dialog->con = args->con;
        dialog->id = args->id;
        dialog->name = args->name;
        dialog->address = args->address;
        dialog->age = args->age;
        status = edit_dialog_graphics_init (dialog);
    }

    return status;
}

bool edit_dialog_run (edit_dialog_t *dialog)
{
    bool status = false;

    if (dialog != NULL)
    {
        char buff[5] = {0};
        gtk_entry_set_text (GTK_ENTRY (dialog->widgets->txt_name), dialog->name);
        gtk_entry_set_text (GTK_ENTRY (dialog->widgets->txt_address), dialog->address);
        snprintf (buff, 5, "%d", dialog->age);
        gtk_entry_set_text (GTK_ENTRY (dialog->widgets->txt_age), buff);
        gtk_dialog_run (GTK_DIALOG (dialog->widgets->dialog));
        status = true;
    }

    return status;
}

bool edit_dialog_close (edit_dialog_t *dialog)
{
    bool status = false;

    if (dialog != NULL)
    {
        g_slice_free (edit_dialog_widgets_t, dialog->widgets);
        memset (dialog, 0, sizeof (edit_dialog_t));
        status = true;
    }

    return status;
}

static bool edit_dialog_graphics_init (edit_dialog_t *dialog)
{
    GtkBuilder *builder;

    dialog->widgets = g_slice_new (edit_dialog_widgets_t);

    builder = gtk_builder_new ();

    gtk_builder_add_from_file (builder, "resources/edit_window.glade", NULL);

    dialog->widgets->dialog      = GTK_WIDGET (gtk_builder_get_object (builder, "edit_window"));
    dialog->widgets->txt_name    = GTK_WIDGET (gtk_builder_get_object (builder, "txt_name"));
    dialog->widgets->txt_address = GTK_WIDGET (gtk_builder_get_object (builder, "txt_address"));
    dialog->widgets->txt_age     = GTK_WIDGET (gtk_builder_get_object (builder, "txt_age"));
    dialog->widgets->bt_confirm  = GTK_WIDGET (gtk_builder_get_object (builder, "bt_confirm"));
    dialog->widgets->bt_cancel   = GTK_WIDGET (gtk_builder_get_object (builder, "bt_cancel"));

    gtk_builder_connect_signals (builder, dialog);

    g_object_unref (builder);

    return true;
}

void on_edit_window_destroy (void)
{

}

void on_bt_edit_confirm_clicked (GtkButton *bt_edit, void *data)
{
    edit_dialog_t *d = (edit_dialog_t *)data;
    char *name = (char *) gtk_entry_get_text (GTK_ENTRY (d->widgets->txt_name));
    char *address = (char *) gtk_entry_get_text (GTK_ENTRY (d->widgets->txt_address));
    char *age = (char *) gtk_entry_get_text (GTK_ENTRY (d->widgets->txt_age));

    GtkWidget *dialog = gtk_message_dialog_new (GTK_WINDOW (d->widgets->dialog),
                                                GTK_DIALOG_MODAL,
                                                GTK_MESSAGE_QUESTION,
                                                GTK_BUTTONS_OK_CANCEL,
                                                "%s", 
                                                "This content is about to be modified. Are you sure?");

    int answer = gtk_dialog_run (GTK_DIALOG (dialog));
    if (answer == GTK_RESPONSE_OK)
        d->con->on_update (d->con->object, d->id, name, address, age);

    gtk_widget_destroy (GTK_WIDGET (dialog));
    gtk_widget_destroy (GTK_WIDGET (d->widgets->dialog));
}

void on_bt_edit_cancel_clicked (GtkButton *bt_edit, void *data)
{
    edit_dialog_t *dialog = (edit_dialog_t *)data;
    gtk_widget_destroy (GTK_WIDGET (dialog->widgets->dialog));
}