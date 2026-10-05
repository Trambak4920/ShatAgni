#include "SlipRing_Interface.hpp"
#include "stm32f4xx_hal.h"

// Assuming SPI3 is routed across the Tungsten Slip Rings
extern SPI_HandleTypeDef hspi3; 

void SlipRing_SendMotorCommand(float pwm) {
    uint8_t tx_data[4];
    // Pack float to bytes
    memcpy(tx_data, &pwm, sizeof(float));
    HAL_SPI_Transmit(&hspi3, tx_data, 4, HAL_MAX_DELAY);
}

Vector3 SlipRing_ReadStableIMU() {
    uint8_t rx_data[12];
    uint8_t tx_data[12] = {0};
    HAL_SPI_TransmitReceive(&hspi3, tx_data, rx_data, 12, HAL_MAX_DELAY);
    
    Vector3 data;
    memcpy(&data, rx_data, sizeof(Vector3));
    return data;
}
