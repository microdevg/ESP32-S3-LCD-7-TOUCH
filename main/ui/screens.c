#include <string.h>

#include "screens.h"
#include "images.h"
#include "fonts.h"
#include "actions.h"
#include "vars.h"
#include "styles.h"
#include "ui.h"

#include <string.h>

objects_t objects;
lv_obj_t *tick_value_change_obj;
uint32_t active_theme_index = 0;

static lv_meter_scale_t * scale0;
static lv_meter_indicator_t * indicator1;

void create_screen_main() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.main = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 800, 480);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            lv_obj_set_pos(obj, 484, 60);
            lv_obj_set_size(obj, 100, 50);
            lv_obj_add_event_cb(obj, action_counter_refresh, LV_EVENT_PRESSED, (void *)1);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_add_event_cb(obj, action_counter_update, LV_EVENT_PRESSED, (void *)1);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "+1");
                }
            }
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            lv_obj_set_pos(obj, 620, 60);
            lv_obj_set_size(obj, 100, 50);
            lv_obj_add_event_cb(obj, action_counter_refresh, LV_EVENT_PRESSED, (void *)-1);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "-1");
                }
            }
        }
        {
            // Counter_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.counter_label = obj;
            lv_obj_set_pos(obj, 515, 19);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_recolor(obj, true);
            lv_obj_add_event_cb(obj, action_counter_update, LV_EVENT_RELEASED, (void *)0);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xff335aa9), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            lv_obj_t *obj = lv_switch_create(parent_obj);
            lv_obj_set_pos(obj, 595, 295);
            lv_obj_set_size(obj, 50, 25);
        }
        {
            lv_obj_t *obj = lv_canvas_create(parent_obj);
            lv_obj_set_pos(obj, 185, 295);
            lv_obj_set_size(obj, 180, 100);
        }
        {
            lv_obj_t *obj = lv_meter_create(parent_obj);
            lv_obj_set_pos(obj, 515, 140);
            lv_obj_set_size(obj, 180, 180);
            {
                lv_meter_scale_t *scale = lv_meter_add_scale(obj);
                scale0 = scale;
                lv_meter_set_scale_ticks(obj, scale, 41, 1, 5, lv_color_hex(0xffa0a0a0));
                lv_meter_set_scale_major_ticks(obj, scale, 8, 3, 10, lv_color_hex(0xff000000), 10);
                lv_meter_set_scale_range(obj, scale, 0, 100, 300, 120);
                {
                    lv_meter_indicator_t *indicator = lv_meter_add_needle_line(obj, scale, 3, lv_color_hex(0xff0000ff), -28);
                    indicator1 = indicator;
                    lv_meter_set_indicator_value(obj, indicator, 30);
                }
            }
        }
        {
            lv_obj_t *obj = lv_keyboard_create(parent_obj);
            objects.obj0 = obj;
            lv_obj_set_pos(obj, 40, 156);
            lv_obj_set_size(obj, 409, 309);
            lv_obj_add_event_cb(obj, action_new_key, LV_EVENT_PRESSED, (void *)1);
            lv_obj_set_style_align(obj, LV_ALIGN_DEFAULT, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // textarea
            lv_obj_t *obj = lv_textarea_create(parent_obj);
            objects.textarea = obj;
            lv_obj_set_pos(obj, 40, 42);
            lv_obj_set_size(obj, 409, 80);
            lv_textarea_set_max_length(obj, 128);
            lv_textarea_set_one_line(obj, false);
            lv_textarea_set_password_mode(obj, false);
        }
    }
    lv_keyboard_set_textarea(objects.obj0, objects.textarea);
    
    tick_screen_main();
}

void tick_screen_main() {
    {
        const char *new_val = get_var_counter_string();
        const char *cur_val = lv_label_get_text(objects.counter_label);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.counter_label;
            lv_label_set_text(objects.counter_label, new_val);
            tick_value_change_obj = NULL;
        }
    }
}



typedef void (*tick_screen_func_t)();
tick_screen_func_t tick_screen_funcs[] = {
    tick_screen_main,
};
void tick_screen(int screen_index) {
    tick_screen_funcs[screen_index]();
}
void tick_screen_by_id(enum ScreensEnum screenId) {
    tick_screen_funcs[screenId - 1]();
}

void create_screens() {
    lv_disp_t *dispp = lv_disp_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    
    create_screen_main();
}
