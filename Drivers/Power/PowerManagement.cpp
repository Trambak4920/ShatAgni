#include "PowerManagement.h"
#include "stm32f4xx_hal.h"

extern ADC_HandleTypeDef hadc2;

float Power_GetBatteryVoltage() {
    HAL_ADC_Start(&hadc2);
    HAL_ADC_PollForConversion(&hadc2, 10);
    uint32_t raw = HAL_ADC_GetValue(&hadc2);
    HAL_ADC_Stop(&hadc2);
    
    // Assuming 3.3V reference and 1/2 voltage divider
    float voltage = (float)raw * (3.3f / 4095.0f) * 2.0f;
    return voltage;
}
