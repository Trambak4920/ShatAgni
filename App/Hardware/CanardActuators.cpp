#include "CanardActuators.hpp"
#include "stm32f4xx_hal.h"

extern TIM_HandleTypeDef htim4;

void CanardActuators_SetDeflection(Vector3 cmd) {
    // Map normalized -1.0 to 1.0 to PWM pulse widths (e.g., 1000us to 2000us)
    uint16_t pwm_x = 1500 + (cmd.x * 500);
    uint16_t pwm_y = 1500 + (cmd.y * 500);
    
    __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, pwm_x);
    __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, pwm_y);
}
