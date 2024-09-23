#ifndef __APP_H
#define __APP_H


#ifdef ARDUINO
    #include "Port/Display.h"
    #define INIT_DONE() \
    do{ \
        xTaskNotifyGive(DISPLAY_TASK_HANDLE); \
    }while(0) \

#else
    
    #define INIT_DONE() \
    do{ \
    }while(0) \

#endif

void App_Init();
void App_UnInit();
#endif