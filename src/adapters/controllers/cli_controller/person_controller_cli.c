#include <person_controller_cli.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef enum 
{
    person_add = 1,
    person_remove,
    person_update,
    person_find,
    person_getall
} person_controller_options;

cli_option_t option_list[] = 
{
    {.index = person_add,    .text = "Add Person"},
    {.index = person_remove, .text = "Remove Person"},
    {.index = person_update, .text = "Update Person"},
    {.index = person_find,   .text = "Find Person"},
    {.index = person_getall, .text = "Get all Persons"},
};

static void *person_controller_cli_on_selected (uint8_t index, void *data);
static bool person_controller_cli_add (person_controller_cli_t *cli_controller);
static bool person_controller_cli_remove (person_controller_cli_t *cli_controller);
static bool person_controller_cli_update (person_controller_cli_t *cli_controller);
static bool person_controller_cli_find (person_controller_cli_t *cli_controller);
static bool person_controller_cli_getall (person_controller_cli_t *cli_controller);
static void person_controller_cli_print (person_controller_cli_t *cli_controller, const person_t *person_list, unsigned int amount);


bool person_controller_cli_init (void *object)
{
    bool status = false;

    if (object != NULL)
    {
        person_controller_cli_t *cli_controller = (person_controller_cli_t *)object;

        memset (cli_controller, 0, sizeof (person_controller_cli_t));

        cli_controller->base.object = cli_controller;

        cli_controller->base.init  = person_controller_cli_init;
        cli_controller->base.open  = person_controller_cli_open;
        cli_controller->base.run   = person_controller_cli_run;
        cli_controller->base.close = person_controller_cli_close;

        cli_init (&cli_controller->cli);

        cli_controller->cli.on_selected = person_controller_cli_on_selected;

        status = true;
    }

    return status;
}

bool person_controller_cli_open (void *object, person_controller_args_t *args)
{
    bool status = false;

    if (object != NULL && args != NULL)
    {
        person_controller_cli_t *cli_controller = (person_controller_cli_t *)object;

        cli_controller->service = args->service;

        cli_open (&cli_controller->cli, option_list, sizeof (option_list) / sizeof (option_list[0]));

        status = true;
    }

    return status;
}

bool person_controller_cli_run (void *object)
{
    person_controller_cli_t *cli_controller = (person_controller_cli_t *)object;
    cli_run (&cli_controller->cli, cli_controller);
    return true;
}

bool person_controller_cli_close (void *object)
{
    bool status = false;

    if (object != NULL)
    {
        person_controller_cli_t *cli_controller = (person_controller_cli_t *)object;

        memset (cli_controller, 0, sizeof (person_controller_cli_t));
        status = true;
    }

    return status;
}

person_controller_base_t person_controller_cli_create (person_controller_args_t *args)
{
    static person_controller_cli_t cli_controller;

    person_controller_cli_init (&cli_controller);
    person_controller_cli_open (&cli_controller, args);

    return cli_controller.base;
}

static void *person_controller_cli_on_selected (uint8_t index, void *data)
{
    person_controller_cli_t *cli_controller = (person_controller_cli_t *)data;

    switch (index)
    {
    case person_add:
        person_controller_cli_add (cli_controller);
        break;

    case person_remove:
        person_controller_cli_remove (cli_controller);
        break;

    case person_update:
        person_controller_cli_update (cli_controller);
        break;

    case person_find:
        person_controller_cli_find (cli_controller);
        break;

    case person_getall:
        person_controller_cli_getall (cli_controller);
        break;
    
    default:
        break;
    }

    return NULL;
}

static bool person_controller_cli_add (person_controller_cli_t *cli_controller)
{
    char name[PERSON_NAME_LEN] = "";
    char address[PERSON_ADDRESS_LEN] = "";
    int age;

    printf ("Enter a Name: ");
    fgets (name, PERSON_NAME_LEN, stdin);
    name[strlen(name) - 1] = 0;


    printf ("Enter an Address: ");
    fgets (address, PERSON_ADDRESS_LEN, stdin);
    address[strlen(address) - 1] = 0;

    printf ("Enter an Age: ");
    scanf ("%d", &age);
    getchar ();

    person_t person = person_create (name, address, age);
    cli_controller->service->base.add (cli_controller->service->base.object, &person);
    return true;
}

static bool person_controller_cli_remove (person_controller_cli_t *cli_controller)
{
    person_t person;
    printf ("Type an ID to delete: ");
    scanf ("%d", &person.id);
    getchar ();

    cli_controller->service->base.remove (cli_controller->service->base.object, &person);
    return true;
}

static bool person_controller_cli_update (person_controller_cli_t *cli_controller)
{
    int id;
    char name[PERSON_NAME_LEN] = "";
    char address[PERSON_ADDRESS_LEN] = "";
    int age;

    printf ("Type an ID to update: ");
    scanf ("%d", &id);
    getchar ();

    printf ("Enter a Name: ");
    fgets (name, PERSON_NAME_LEN, stdin);
    name[strlen(name) - 1] = 0;

    printf ("Enter an Address: ");
    fgets (address, PERSON_ADDRESS_LEN, stdin);
    address[strlen(address) - 1] = 0;

    printf ("Enter an Age: ");
    scanf ("%d", &age);
    getchar ();

    person_t person = person_create (name, address, age);
    person.id = id;

    cli_controller->service->base.update (cli_controller->service->base.object, &person);
    return true;
}

static bool person_controller_cli_find (person_controller_cli_t *cli_controller)
{
    char name[PERSON_NAME_LEN] = "";
    bool status = false;

    printf ("Type a nam to find: ");
    fgets (name, PERSON_NAME_LEN, stdin);
    name [strlen (name) - 1] = 0;

    person_t person = person_create (name, NULL, 0);

    status = cli_controller->service->base.find (cli_controller->service->base.object, &person);

    if (status == true)
    {
        printf ("Found: ");
        person_controller_cli_print (cli_controller, &person, 1);
    }
    else 
    {
        printf ("Not found.\n");
    }

    return status;
}   

static bool person_controller_cli_getall (person_controller_cli_t *cli_controller)
{
    person_t *person_list = NULL;
    unsigned int amount = 0;

    cli_controller->service->base.getall (cli_controller->service->base.object, &person_list, &amount);

    person_controller_cli_print (cli_controller, person_list, amount);

    free (person_list);
    return true;
}

static void person_controller_cli_print (person_controller_cli_t *cli_controller, const person_t *person_list, unsigned int amount)
{
    (void)cli_controller;

    for (unsigned int i = 0; i < amount; i++)
    {
        person_t *p = (person_t *)&person_list[i];
        printf ("ID: %d, Name: %s, Address: %s, Age: %d\n", p->id, p->name, p->address, p->age);
    }
}