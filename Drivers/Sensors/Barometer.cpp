#include "Barometer.h"
#include "stm32f4xx_hal.h"

extern I2C_HandleTypeDef hi2c1;

float Baro_ReadPressure() {
    uint8_t data[3] = {0};
    uint8_t reg = 0xF7; // MSB of Pressure
    HAL_I2C_Master_Transmit(&hi2c1, 0xEC, &reg, 1, 10);
    HAL_I2C_Master_Receive(&hi2c1, 0xEC, data, 3, 10);
    
    int32_t raw = (data[0] << 12) | (data[1] << 4) | (data[2] >> 4);
    return (float)raw / 256.0f; // Convert to Pascals (Example for BMP280)
}
