#include <cli.h>
#include <string.h>
#include <stdio.h>

static void cli_print_menu (cli_t *cli);
static uint8_t cli_get_option (cli_t *cli);
static void cli_option_exec (cli_t *cli, uint8_t choose, void *data);

bool cli_init (cli_t *cli)
{
    bool status = false;

    if (cli != NULL)
    {
        memset (cli, 0, sizeof (cli_t));
        status = true;
    }

    return status;
}

bool cli_open (cli_t *cli, cli_option_t *option_list, uint8_t option_amount)
{
    bool status = false;

    if (cli != NULL)
    {
        cli->option_list = option_list;
        cli->option_amount = option_amount;
        status = true;
    }

    return status;
}

bool cli_run (cli_t *cli, void *data)
{
    bool status = false;
    uint8_t choose;

    do 
    {
        cli_print_menu (cli);

        choose = cli_get_option (cli);

        cli_option_exec (cli, choose, data);
    } while (choose != 0);

    return status;
}

static void cli_print_menu (cli_t *cli)
{
    for (uint8_t i = 0; i < cli->option_amount; i++)
    {
        cli_option_t *op = &cli->option_list[i];
        fprintf (stdout, "%d. %s\n", op->index, op->text);
    }

    fprintf (stdout, "0. Quit\n");
}

static uint8_t cli_get_option (cli_t *cli)
{
    (void)cli;
    int choose;
    fprintf (stdout, "Select an option: ");
    scanf ("%d", &choose);
    getchar ();
    putchar ('\n');

    return (uint8_t)choose;
}

static void cli_option_exec (cli_t *cli, uint8_t choose, void *data)
{
    uint8_t i;

    for (i = 0; i < cli->option_amount && choose; i++)
    {
        cli_option_t *op = &cli->option_list[i];
        if (choose == op->index)
        {
            cli->on_selected (op->index, data);
            break;
        }
    }

    if (i == cli->option_amount)
    {
        printf ("This option isn't available.");
    }

    printf ("\n\n");
}