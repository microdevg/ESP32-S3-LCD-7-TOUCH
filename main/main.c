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

// 🎯 SOLUCIÓN: DEFINE LA CONSTANTE TAG
static const char *myTAG = "APP_MAIN"; 


#include <lvgl.h>

static SemaphoreHandle_t lvgl_mux = NULL;


bool lvgl_lock(int timeout_ms)
{
    // Convert timeout in milliseconds to FreeRTOS ticks
    // If `timeout_ms` is set to -1, the program will block until the condition is met
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

// void button_event_cb(lv_event_t *e) {
//     // Imprime un mensaje en la consola serial al presionar el botón
//     ESP_LOGI("LVGL", "Button Clicked!"); 
// }


// -------------------------------------------------------------

void app_main()
{
    // ... el código dentro de app_main() permanece igual ...

    waveshare_esp32_s3_rgb_lcd_init(); 
    wavesahre_rgb_lcd_bl_on();  
    
    // Aquí es donde se usa la constante myTAG:
    ESP_LOGI(myTAG, "Inicializando UI de EEZ Studio"); 
    
    // 1. Inicializa la UI (Crea los objetos LVGL)
    
   // create_simple_ui();
    // 2. LLAMAR A LA FUNCIÓN PARA CARGAR LA PANTALLA INICIAL
    // Ejemplo (Asegúrate de que 'screens.h' esté incluido y los nombres sean correctos):
    // loadScreen(SCREEN_ID_SCREEN_1); 
    lvgl_mux = xSemaphoreCreateRecursiveMutex();
    assert(lvgl_mux);

    if (lvgl_lock(-1))
    {
        ui_init();
        // Release the mutex
        lvgl_unlock();
    }
}
    
