#include "HAL/HAL.h"
#include "Wire.h"

void HAL::I2C_Init(bool startScan) {
    uint8_t error=0, address=0;
    int nDevices = 0;
    
    Serial.println("I2C Init");
    Serial.println("Wrie SDA Pin" + String(CONFIG_MCU_SDA_PIN) + ", SCL Pin" + String(CONFIG_MCU_SCL_PIN));
    Wire.begin(CONFIG_MCU_SDA_PIN, CONFIG_MCU_SCL_PIN);
    if (!startScan) {
        return;
    }
    Serial.println("I2C: device scanning...");
    for(address =0 ; address<127; address++){
        Wire.beginTransmission(address);
        error = Wire.endTransmission();
        if(error >0 && error == 4){
            Serial.print("I2C: Unknow error at address 0x");
            if(address<16)
                Serial.print("0");
            Serial.println(address,HEX);
        }
        else if(error == 0){
            Serial.print("I2C: Found device at address 0x");
            if(address<16)
                Serial.print("0");
            Serial.println(address,HEX);
            Serial.println(" !");

            nDevices++;
        }
    }
    Serial.printf("I2C: %d devices was found\r\n", nDevices);
}