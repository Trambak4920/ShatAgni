#pragma once
#include "stm32f4xx_hal.h"

// IMU1 (Spinning Body) - SPI1
#define IMU1_CS_PIN GPIO_PIN_4
#define IMU1_CS_PORT GPIOA

// IMU2 (Stable Free Surface) - SPI2 (Across Slip Ring)
#define IMU2_CS_PIN GPIO_PIN_12
#define IMU2_CS_PORT GPIOB

// GPS - USART2
#define GPS_UART huart2

// Inductive Programming Coil - ADC1 / TIM3
#define INDUCTIVE_ADC_CHANNEL ADC_CHANNEL_0
#define INDUCTIVE_TIM htim3

// Canard Actuators - TIM4 PWM
#define CANARD_PWM_TIM htim4