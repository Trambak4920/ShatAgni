#include "IMU2_StableNav.h"
#include "IMU_Common.hpp"
#include "stm32f4xx_hal.h"

extern SPI_HandleTypeDef hspi2; // SPI2 is routed across the Tungsten Slip Ring

Vector3 IMU2_ReadAccel() {
    uint8_t rx[6] = {0};
    IMU_SPI_Read(0x80 | 0x28, rx, 6); // Read Accel X,Y,Z
    Vector3 accel;
    accel.x = (float)((rx[1] << 8) | rx[0]) * 0.000122f; // Scale to g
    accel.y = (float)((rx[3] << 8) | rx[2]) * 0.000122f;
    accel.z = (float)((rx[5] << 8) | rx[4]) * 0.000122f;
    return accel;
}

Vector3 IMU2_ReadGyro() {
    uint8_t rx[6] = {0};
    IMU_SPI_Read(0x80 | 0x18, rx, 6); // Read Gyro X,Y,Z
    Vector3 gyro;
    gyro.x = (float)((rx[1] << 8) | rx[0]) * 0.070f; // Scale to deg/s
    gyro.y = (float)((rx[3] << 8) | rx[2]) * 0.070f;
    gyro.z = (float)((rx[5] << 8) | rx[4]) * 0.070f;
    return gyro;
}
