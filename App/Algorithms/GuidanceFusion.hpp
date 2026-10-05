#include "GPS_Receiver.h"
#include "stm32f4xx_hal.h"
#include <string.h>

extern UART_HandleTypeDef huart2;
static char gps_buffer[128];
static uint8_t gps_idx = 0;
static bool gps_valid = false;

void GPS_IRQHandler() {
    uint8_t data;
    HAL_UART_Receive(&huart2, &data, 1, 0);
    if (data == '\n') {
        gps_buffer[gps_idx] = '\0';
        gps_idx = 0;
        // Simple NMEA parsing logic would go here
        gps_valid = true; 
    } else {
        if (gps_idx < 127) gps_buffer[gps_idx++] = data;
    }
}

Vector3 GPS_GetPosition() {
    // Parsed from NMEA buffer
    return Vector3(0.0f, 0.0f, 0.0f); 
}

float GPS_GetHDOP() {
    return 1.2f; // Placeholder
}
