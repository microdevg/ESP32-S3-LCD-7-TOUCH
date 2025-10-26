#ifndef EEZ_LVGL_UI_EVENTS_H
#define EEZ_LVGL_UI_EVENTS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

extern void action_counter_refresh(lv_event_t * e);
extern void action_add_counter(lv_event_t * e);
extern void action_counter_update(lv_event_t * e);
extern void action_new_key(lv_event_t * e);


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_EVENTS_H*/