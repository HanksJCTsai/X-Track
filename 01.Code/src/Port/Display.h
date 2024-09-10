#ifndef __DISPLAY_H
#define __DISPLAY_H

#include "App/Configs/Config.h"

#include "lvgl.h"
#include "TFT_eSPI.h"

typedef TFT_eSPI DISPLAY_CLASS;
extern TaskHandle_t DISPLAY_TASK_HANDLE;

void DisplayInit();
void DisplayFaultInit(DISPLAY_CLASS *scr);
void LVPortDisplayInit(DISPLAY_CLASS* scr);
void LVFsIfInit();
void LVPortIndevInit();

#endif