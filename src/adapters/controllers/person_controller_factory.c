#include <person_controller_factory.h>
#include <person_controller_cli.h>
#include <person_controller_gtk.h>

person_controller_base_t person_controller_factory_create (person_controller_type_t type, person_controller_args_t *args)
{
    person_controller_base_t controller_base;

    if (type == person_controller_type_cli)
    {
        controller_base = person_controller_cli_create (args);
    }

    if (type == person_controller_type_gtk)
    {
        controller_base = person_controller_gtk_create (args);
    }

    return controller_base;
}