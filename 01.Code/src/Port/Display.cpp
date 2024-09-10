#include "Display.h"

TaskHandle_t DISPLAY_TASK_HANDLE;
void TaskLvglUpdate(void* parameter)
{
    ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
    for (;;)
    {
        lv_task_handler();
        delay(5);
    }
}

void DisplayInit() {
// Initialize the TFT_eSPI
static DISPLAY_CLASS display;
display.begin();
display.setRotation(0);
display.fillScreen(TFT_BLACK);

// Initialize the LVGL
lv_init();

// Update display in parallel thread.
    xTaskCreate(
        TaskLvglUpdate,
        "LvglThread",
        20000,
        nullptr,
        configMAX_PRIORITIES - 1,
        &DISPLAY_TASK_HANDLE);

}