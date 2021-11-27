#ifndef CLI_H_
#define CLI_H_

#include <view_base.h>

view_base *cli_view_create(void);
bool cli_view_destroy(view_base *view);

#endif /* CLI_H_ */
