/*
 * SPDX-FileCopyrightText: 2023-2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#include "waveshare_rgb_lcd_port.h"


// Demo UI adaptada para pantalla 800x480
void example_lvgl_demo_ui()
{
    // Obtener la pantalla activa
    lv_obj_t *scr = lv_scr_act();

    // ----- Fondo -----
    lv_obj_set_style_bg_color(scr, lv_color_make(200, 230, 255), 0); // Celeste claro
    lv_obj_set_style_bg_grad_color(scr, lv_color_make(180, 210, 250), 0);
    lv_obj_set_style_bg_grad_dir(scr, LV_GRAD_DIR_VER);
    lv_obj_set_style_bg_opa(scr, LV_OPA_COVER, 0);

    // ----- Texto principal -----
    lv_obj_t *label_title = lv_label_create(scr);
    lv_label_set_text(label_title, "IFTS 14");
    lv_obj_set_style_text_font(label_title, &lv_font_montserrat_48, 0);
    lv_obj_set_style_text_color(label_title, lv_color_black(), 0);
    lv_obj_align(label_title, LV_ALIGN_CENTER, 0, -100); // Centrado arriba

    // ----- Texto secundario -----
    lv_obj_t *label_year = lv_label_create(scr);
    lv_label_set_text(label_year, "AÑO 2025");
    lv_obj_set_style_text_font(label_year, &lv_font_montserrat_28, 0);
    lv_obj_set_style_text_color(label_year, lv_color_make(40, 40, 40), 0);
    lv_obj_align_to(label_year, label_title, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);

    // ----- Crear gráfico -----
    lv_obj_t *chart = lv_chart_create(scr);
    lv_obj_set_size(chart, 500, 250);                          // Tamaño más grande para 800x480
    lv_obj_align(chart, LV_ALIGN_CENTER, 0, 100);              // Debajo de los textos
    lv_obj_add_event_cb(chart, draw_event_cb, LV_EVENT_DRAW_PART_BEGIN, NULL);
    lv_obj_set_style_line_width(chart, 0, LV_PART_ITEMS);      // Sin líneas internas

    lv_chart_set_type(chart, LV_CHART_TYPE_SCATTER);

    // Ejes
    lv_chart_set_axis_tick(chart, LV_CHART_AXIS_PRIMARY_X, 10, 5, 10, 1, true, 50);
    lv_chart_set_axis_tick(chart, LV_CHART_AXIS_PRIMARY_Y, 10, 5, 10, 5, true, 80);

    lv_chart_set_range(chart, LV_CHART_AXIS_PRIMARY_X, 0, 200);
    lv_chart_set_range(chart, LV_CHART_AXIS_PRIMARY_Y, 0, 1000);

    lv_chart_set_point_count(chart, 50);

    // Serie de puntos
    lv_chart_series_t *ser = lv_chart_add_series(chart, lv_palette_main(LV_PALETTE_RED), LV_CHART_AXIS_PRIMARY_Y);
    for (int i = 0; i < 50; i++) {
        lv_chart_set_next_value2(chart, ser, lv_rand(0, 200), lv_rand(0, 1000));
    }

    // Timer para agregar datos
    lv_timer_create(add_data, 100, chart);
}


void app_main()
{
    waveshare_esp32_s3_rgb_lcd_init(); // Initialize the Waveshare ESP32-S3 RGB LCD 
    wavesahre_rgb_lcd_bl_on();  //Turn on the screen backlight 
    // wavesahre_rgb_lcd_bl_off(); //Turn off the screen backlight 
    
    ESP_LOGI(TAG, "Display LVGL demos");
    // Lock the mutex due to the LVGL APIs are not thread-safe
    if (lvgl_port_lock(-1)) {
        
        //lv_demo_stress();
       // lv_demo_benchmark();
      //  lv_demo_music();
       //lv_demo_widgets();
       example_lvgl_demo_ui();
       // Release the mutex
        lvgl_port_unlock();
    }


  
}
