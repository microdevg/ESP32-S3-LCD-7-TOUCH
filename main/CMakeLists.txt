

file(GLOB_RECURSE UI "./ui/*.c")

#file(GLOB_RECURSE ST7735S "./../st7735s/*.c")
#file(GLOB_RECURSE SOURCES "*.c")

idf_component_register(
    SRCS ${UI} "waveshare_rgb_lcd_port.c" "main.c" "lvgl_port.c"
    INCLUDE_DIRS "."  REQUIRES "esp_lcd")

idf_component_get_property(lvgl_lib lvgl__lvgl COMPONENT_LIB)
target_compile_options(${lvgl_lib} PRIVATE -Wno-format)
