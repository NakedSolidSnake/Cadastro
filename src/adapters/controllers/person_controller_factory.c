#include <person_controller_factory.h>
#include <person_controller_cli.h>
#include <person_controller_gtk.h>
#include <configuration.h>
#include <string.h>

person_controller_base_t person_controller_factory_create (const char *type, person_controller_args_t *args)
{
    person_controller_base_t controller_base;

    // if (type == person_controller_type_cli)
    if (strcmp (type, CONFIGURATION_CONTROLLER_TYPE_CLI) == 0)
    {
        controller_base = person_controller_cli_create (args);
    }

    // if (type == person_controller_type_gtk)
    if (strcmp (type, CONFIGURATION_CONTROLLER_TYPE_GTK) == 0)
    {
        controller_base = person_controller_gtk_create (args);
    }

    return controller_base;
}