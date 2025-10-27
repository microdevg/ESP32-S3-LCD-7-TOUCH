/*
 * SPDX-FileCopyrightText: 2023-2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */
#include "waveshare_rgb_lcd_port.h"

#include "ui/ui.h"
#include "esp_log.h" 

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "ui/screens.h"

#include <lvgl.h>
#include <string.h>


static SemaphoreHandle_t lvgl_mux = NULL;
char buffer[100]={0};
char counter_string[100] = { 0 };
int32_t counter;
int screen = SCREEN_ID_MAIN;

void action_change_view(lv_event_t * e) {
    screen = (screen == SCREEN_ID_NODES)?SCREEN_ID_MAIN: SCREEN_ID_NODES;
    loadScreen(screen);
}


int32_t get_var_counter() {
    return counter;
}

void set_var_counter(int32_t value) {
    counter = value;
}
const char *get_var_counter_string() {
    return counter_string;
}

void set_var_counter_string(const char *value) {
    strncpy(counter_string, value, sizeof(counter_string) / sizeof(char));
    counter_string[sizeof(counter_string) / sizeof(char) - 1] = 0;
}
 void action_new_key(lv_event_t * e){
    lv_obj_t *kb = lv_event_get_target(e);
    lv_obj_t *ta = lv_keyboard_get_textarea(kb);
    if (!ta)
    {
        printf("ERROR: No hay textarea asociado al teclado\n");
        return;
    }
        const char *text = lv_textarea_get_text(ta);
        printf(text);
}


void action_counter_refresh(lv_event_t * e){
    int c = get_var_counter() + (int)e->user_data;
    set_var_counter(c);
    sprintf(buffer,"Counter:%ld\n",get_var_counter());
    printf(buffer);
    printf("el contenido del buffer es:%s\n",buffer);
    set_var_counter_string(buffer);
}

void action_counter_update(lv_event_t * e){
   printf("refresh text\n");
}



bool lvgl_lock(int timeout_ms)
{
    const TickType_t timeout_ticks = (timeout_ms == -1) ? portMAX_DELAY : pdMS_TO_TICKS(timeout_ms);
    return xSemaphoreTakeRecursive(lvgl_mux, timeout_ticks) == pdTRUE;
}

void lvgl_unlock(void)
{
    xSemaphoreGiveRecursive(lvgl_mux);
}


// Función para crear la interfaz de usuario simple (reemplaza ui_init temporalmente)
void create_simple_ui() {
    // 1. Obtiene la pantalla activa (el fondo)
    lv_obj_t *scr = lv_scr_act();
    
    // 2. Crea el botón
    lv_obj_t *btn = lv_btn_create(scr);
    
    // Centra el botón en la pantalla
    lv_obj_center(btn);
    
    // Opcional: Establece el tamaño del botón
    lv_obj_set_size(btn, 150, 50);

    // 3. Crea una etiqueta (texto) dentro del botón
    lv_obj_t *label = lv_label_create(btn);
    
    // Establece el texto
    lv_label_set_text(label, "ifts14");
    
    // Centra la etiqueta dentro del botón
    lv_obj_center(label);

    // 4. (Opcional) Añade un evento para confirmar que es interactivo
    // lv_obj_add_event_cb(btn, button_event_cb, LV_EVENT_CLICKED, NULL); 
}


void app_main()
{
    waveshare_esp32_s3_rgb_lcd_init(); 
    wavesahre_rgb_lcd_bl_on();  
   // create_simple_ui();
    lvgl_mux = xSemaphoreCreateRecursiveMutex();
    assert(lvgl_mux);
    if (lvgl_lock(-1))
    {
        ui_init();
        // Release the mutex
        lvgl_unlock();
    }
    while(1){
        ui_tick(); // Con esta funcion refresco pantalla
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}
    
