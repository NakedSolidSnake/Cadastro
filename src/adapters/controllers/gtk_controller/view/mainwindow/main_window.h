#ifndef MAIN_WINDOW_H_
#define MAIN_WINDOW_H_

#include <stdbool.h>

typedef struct 
{
    void *window;
} main_window_widgets_t;

typedef struct 
{
    main_window_widgets_t *widgets;
    int argc;
    char **argv;
} main_window_t;

typedef struct 
{
    int argc;
    char **argv;
} main_window_args_t;

bool main_window_init (main_window_t *window);
bool main_window_open (main_window_t *window, main_window_args_t *args);
bool main_window_run (main_window_t *window);
bool main_window_close (main_window_t *window);

#endif /* MAIN_WINDOW_H_ */
