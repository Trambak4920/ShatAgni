#pragma once
#include "stm32f4xx_hal.h"
// Shared SPI/I2C read/write functions
bool IMU_SPI_Read(uint8_t reg, uint8_t* data, uint16_t len);
