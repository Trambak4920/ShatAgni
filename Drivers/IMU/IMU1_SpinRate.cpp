#include "IMU1_SpinRate.h"
#include "stm32f4xx_hal.h"

extern SPI_HandleTypeDef hspi1;

float IMU1_ReadRollRate() {
    uint8_t tx[2] = {0x80 | 0x28, 0x00}; // Read register 0x28 (GYRO_XOUT_L)
    uint8_t rx[2] = {0};
    HAL_GPIO_WritePin(IMU1_CS_PORT, IMU1_CS_PIN, GPIO_PIN_RESET);
    HAL_SPI_TransmitReceive(&hspi1, tx, rx, 2, HAL_MAX_DELAY);
    HAL_GPIO_WritePin(IMU1_CS_PORT, IMU1_CS_PIN, GPIO_PIN_SET);
    
    int16_t raw = (rx[1] << 8) | rx[0];
    return (float)raw * 0.070f; // Scale factor for rad/s
}
