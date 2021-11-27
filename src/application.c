#include <application.h>

bool application_init(application_t *app, view_base *view, repository_base *repository)
{
    bool status = false;

    if (app && view && repository)
    {
        app->repository = repository;
        app->view = view;

        status = true;
    }

    return status;
}

bool application_run(application_t *app)
{
    bool status = false;

    do 
    {
        if (app->view->init(app->view->object) == false)
            break;

        if (app->view->exec(app->view->object, app->repository) == false)
            break;

        status = true;

    } while (false);

    return status;
}