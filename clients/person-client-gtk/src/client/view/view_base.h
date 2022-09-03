#ifndef VIEW_BASE_H_
#define VIEW_BASE_H_

#include <person.h>
#include <array_list.h>

typedef enum 
{
    message_info,
    message_warning,
    message_question,
    message_error
} message_type_t;

typedef enum 
{
    dialog_button_none,
    dialog_button_ok,
    dialog_button_close,
    dialog_button_cancel,
    dialog_button_yes_no,
    dialog_button_ok_cancel
} dialog_button_t;


typedef struct 
{
    void *object;
    void (*set_all_persons) (void *object, array_list_t *array, unsigned int amount);
    int (*show_dialog_message) (void *object, const char *message, message_type_t type, dialog_button_t button_type);
} view_base_t;


#endif /* VIEW_BASE_H_ */
