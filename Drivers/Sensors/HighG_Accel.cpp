#include "HighG_Accel.h"
#include "stm32f4xx_hal.h"

extern ADC_HandleTypeDef hadc1;

float HighG_ReadImpact() {
    HAL_ADC_Start(&hadc1);
    HAL_ADC_PollForConversion(&hadc1, 10);
    uint32_t raw = HAL_ADC_GetValue(&hadc1);
    HAL_ADC_Stop(&hadc1);
    
    // Map 12-bit ADC (0-4095) to 0-10000G range
    return (float)raw * (10000.0f / 4095.0f);
}
