#include "sdkconfig.h"
#include "freertos/FreeRTOS.h" // Librería necesaria para usar FreeRTOS
#include "freertos/task.h" // Librería necesaria para usar las tareas de FreeRTOS
#include "driver/gpio.h" // Librería necesaria para manejar los pines GPIO

#define LED_GPIO GPIO_NUM_2 // Pin donde está conectado el LED

// Duraciones en milisegundos para el código Morse
#define DOT_MS 200
#define DASH_MS 500
#define BETWEEN_SYMBOLS_MS 200
#define BETWEEN_LETTERS_MS 500

static void dot(void)
{
    gpio_set_level(LED_GPIO, 1);
    vTaskDelay((DOT_MS) / portTICK_PERIOD_MS);
    gpio_set_level(LED_GPIO, 0);
    vTaskDelay(pdMS_TO_TICKS(BETWEEN_SYMBOLS_MS));
}

static void dash(void)
{
    gpio_set_level(LED_GPIO, 1);
    vTaskDelay((DASH_MS) / portTICK_PERIOD_MS);
    gpio_set_level(LED_GPIO, 0);
    vTaskDelay(pdMS_TO_TICKS(BETWEEN_SYMBOLS_MS));
}

static void sos(void)
{
    // S: ...
    for (int i = 0; i < 3; ++i) dot();
    vTaskDelay((BETWEEN_LETTERS_MS) / portTICK_PERIOD_MS);
    // O: ---
    for (int i = 0; i < 3; ++i) dash();
    vTaskDelay(pdMS_TO_TICKS(BETWEEN_LETTERS_MS));
    // S: ...
    for (int i = 0; i < 3; ++i) dot();
}

void app_main(void)
{
    // Configure the LED GPIO
    gpio_reset_pin(LED_GPIO);
    gpio_set_direction(LED_GPIO, GPIO_MODE_OUTPUT);

    while (1) {
        sos();
        printf("Cesarin pin pin \n");
        vTaskDelay((1000) / portTICK_PERIOD_MS); // Pausa entre repeticiones
    }
}