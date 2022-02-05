#ifndef CLI_H_
#define CLI_H_

#include <stdbool.h>
#include <stdint.h>

typedef void *(*cli_event_t) (uint8_t index, void *data);

typedef struct 
{
    uint8_t index;
    char *text;
} cli_option_t;

typedef struct 
{
    cli_option_t *option_list;
    uint8_t option_amount;
    cli_event_t on_selected;
} cli_t;

bool cli_init (cli_t *cli);
bool cli_open (cli_t *cli, cli_option_t *option_list, uint8_t option_amount);
bool cli_run (cli_t *cli, void *data);

#endif /* CLI_H_ */
