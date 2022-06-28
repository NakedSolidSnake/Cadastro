#ifndef GTK_VIEW_H_
#define GTK_VIEW_H_

#include <main_window.h>

typedef struct 
{
    main_window_t main;
} gtk_view_t;

typedef struct 
{
    int argc;
    char **argv;
} gtk_view_args_t;

bool gtk_view_init (gtk_view_t *view);
bool gtk_view_open (gtk_view_t *view, gtk_view_args_t *args);
bool gtk_view_run (gtk_view_t *view);
bool gtk_view_close (gtk_view_t *view);

#endif /* GTK_VIEW_H_ */
