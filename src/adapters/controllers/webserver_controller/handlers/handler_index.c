#include "handlers.h"
#include <string.h>
#include <stdlib.h>

int handler_index (struct mg_connection *conn, void *data)
{
    char path [1024] = {0};

    const struct mg_request_info *ri = mg_get_request_info (conn);

    const char *root = mg_get_option (mg_get_context (conn), "document_root");

    strncpy (path, root, sizeof (path));

    if (strcmp (ri->local_uri, "/") == 0)
    {
        strncat (path, "/index.html", sizeof (path) - strlen (root));
    }
    else 
    {
        strncat (path, ri->local_uri, sizeof (path) - strlen (root));
    }

    mg_send_file (conn, path);

    return 200;
}