#pragma once
/*
+------------------------------------------------------+
|  MPU9250 9-Axis Gyro Accelerator Magnetometer Module |
+------------------------------------------------------+
*/
#include "HAL.h"
#include "MPU9250.h"

static MPU9250 mpu9250;

void HAL::IMU_Init() {
    if (!mpu9250.setup(0x68)) {
        Serial.println("MPU connection failed.");
    }
}

void HAL::IMU_Update() {
    IMU_INFO_T imu_info;
    mpu9250.update();
    imu_info.ax = mpu9250.getAccX();
    imu_info.ay = mpu9250.getAccY();
    imu_info.az = mpu9250.getAccZ();
    imu_info.gx = mpu9250.getGyroX();
    imu_info.gy = mpu9250.getGyroY();
    imu_info.gz = mpu9250.getGyroZ();
    imu_info.mx = mpu9250.getMagX();
    imu_info.my = mpu9250.getMagY();
    imu_info.mz = mpu9250.getMagZ();
    imu_info.roll = mpu9250.getRoll();
    imu_info.yaw = mpu9250.getYaw();
    imu_info.pitch = mpu9250.getPitch();
    //Update IMU data to Account System
    //AccountSystem::UpdateIMU(&imu_info);
}