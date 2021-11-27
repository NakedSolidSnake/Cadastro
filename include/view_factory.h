#ifndef VIEW_FACTORY_H_
#define VIEW_FACTORY_H_

#include <view_base.h>

view_base *view_create(const char *type);
bool view_destroy(const char *type, view_base *view);

#endif /* VIEW_FACTORY_H_ */
