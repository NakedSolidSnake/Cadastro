#ifndef VIEW_BASE_H_
#define VIEW_BASE_H_

#include <stdbool.h>
#include <repository.h>

typedef struct 
{
    void *object;
    bool (*init)(void *object);
    bool (*exec)(void *object, repository_base *repository);
} view_base;

#endif /* VIEW_BASE_H_ */
