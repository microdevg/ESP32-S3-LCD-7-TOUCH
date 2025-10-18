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
            // example
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.example = obj;
            lv_obj_set_pos(obj, LV_PCT(100), LV_PCT(100));
            lv_obj_set_size(obj, LV_PCT(20), LV_PCT(20));
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_EDITED);
            lv_label_set_text(obj, "Hello, world!");
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            lv_obj_set_pos(obj, 129, 46);
            lv_obj_set_size(obj, 100, 50);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Button");
                }
            }
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            lv_obj_set_pos(obj, 300, 46);
            lv_obj_set_size(obj, 100, 50);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Button");
                }
            }
        }
        {
            // my
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.my = obj;
            lv_obj_set_pos(obj, 491, 71);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_my);
        }
        {
            lv_obj_t *obj = lv_spinner_create(parent_obj, 1000, 60);
            lv_obj_set_pos(obj, 350, 337);
            lv_obj_set_size(obj, 80, 80);
        }
        {
            lv_obj_t *obj = lv_meter_create(parent_obj);
            lv_obj_set_pos(obj, 286, 119);
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
            // webserver
            lv_obj_t *obj = lv_qrcode_create(parent_obj, 160, lv_color_hex(0xff20429f), lv_color_hex(0xffe2f5fe));
            objects.webserver = obj;
            lv_obj_set_pos(obj, 49, 160);
            lv_obj_set_size(obj, 160, 160);
            lv_qrcode_update(obj, "http://my-esp.32.com", 20);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
        }
        {
            // web-label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.web_label = obj;
            lv_obj_set_pos(obj, 44, 127);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_EDITED);
            lv_label_set_text(obj, "Webserver configuracion");
        }
    }
    
    tick_screen_main();
}

void tick_screen_main() {
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
