#include <stdio.h>
#include <person_client_gtk.h>

int main (int argc, char *argv[])
{
    person_client_args_t args = 
    {
        .argc = argc,
        .argv = argv
    };

    person_client_gtk_t client;

    person_client_gtk_init (&client);
    person_client_gtk_open (&client, &args);
    person_client_gtk_run (&client);
    person_client_gtk_close (&client);
    return 0;
}