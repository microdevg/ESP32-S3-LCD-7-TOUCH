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

#include <lvgl.h>
#include <string.h>


static SemaphoreHandle_t lvgl_mux = NULL;

bool lvgl_lock(int timeout_ms)
{
    const TickType_t timeout_ticks = (timeout_ms == -1) ? portMAX_DELAY : pdMS_TO_TICKS(timeout_ms);
    return xSemaphoreTakeRecursive(lvgl_mux, timeout_ticks) == pdTRUE;
}

void lvgl_unlock(void)
{
    xSemaphoreGiveRecursive(lvgl_mux);
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
    
