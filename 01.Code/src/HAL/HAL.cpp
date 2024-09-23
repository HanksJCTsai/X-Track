
#include "HAL.h"
#include "APP/Version/Version.h"

#define DISP_HOR_RES         CONFIG_SCREEN_HOR_RES
#define DISP_VER_RES         CONFIG_SCREEN_VER_RES
#define DISP_BUF_SIZE        CONFIG_SCREEN_BUFFER_SIZE
extern lv_color_t* LV_DISP_BUF_P;

void HAL::Init()
{
    Serial.begin(115200);
    Serial.println(VERSION_FIRMWARE_NAME);
    Serial.println("Version: " VERSION_SOFTWARE);
    Serial.println("Author: " VERSION_AUTHOR_NAME);

    LV_DISP_BUF_P = static_cast<lv_color_t*>(malloc(DISP_BUF_SIZE * sizeof(lv_color_t)));
    if (LV_DISP_BUF_P == nullptr)
        LV_LOG_WARN("lv_port_disp_init malloc failed!\n");
    
    HAL::BT_Init();
    HAL::Power_Init();
    HAL::Backlight_Init();
    HAL::Encoder_Init();
    HAL::Buzz_init();
    HAL::Audio_Init();
    HAL::SD_Init();
    HAL::I2C_Init(true);
    HAL::IMU_Init();
    HAL::Audio_PlayMusic("Startup");
}

void HAL::Update()
{
    HAL::Power_Update();
    HAL::Encoder_Update();
    HAL::Audio_Update();
    HAL::IMU_Update();
    HAL::BT_Update();
    __IntervalExecute(HAL::SD_Update(), 500);
}