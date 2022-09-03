#include <stdlib.h>
#include <person_client_gtk.h>
#include <configuration.h>

int main (int argc, char *argv[])
{

    configuration_t conf;

    configuration_init (&conf);

    if (configuration_load (&conf) == false)
    {
        return EXIT_FAILURE;
    }

    person_client_args_t args = 
    {
        .argc = argc,
        .argv = argv,
        .host = conf.address,
        .port = conf.port,
        .endpoint = conf.endpoint
    };

    person_client_gtk_t client;

    person_client_gtk_init (&client);
    person_client_gtk_open (&client, &args);
    person_client_gtk_run (&client);
    person_client_gtk_close (&client);
    return 0;
}