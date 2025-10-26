#ifndef EEZ_LVGL_UI_VARS_H
#define EEZ_LVGL_UI_VARS_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

// enum declarations



// Flow global variables

enum FlowGlobalVariables {
    FLOW_GLOBAL_VARIABLE_COUNTER = 0,
    FLOW_GLOBAL_VARIABLE_COUNTER_STRING = 1
};

// Native global variables

extern int32_t get_var_counter();
extern void set_var_counter(int32_t value);
extern const char *get_var_counter_string();
extern void set_var_counter_string(const char *value);


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_VARS_H*/