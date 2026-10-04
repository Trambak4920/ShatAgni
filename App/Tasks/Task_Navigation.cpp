#include "Task_Navigation.hpp"
#include "GuidanceFusion.hpp"
#include "IMU2_StableNav.h"
#include "GPS_Receiver.h"
#include "CanardActuators.hpp"
#include "FreeRTOS.h"
#include "task.h"

// Instantiate Navigation Algorithms
GuidanceFusion navigator;

extern "C" void StartNavigationTask(void *argument) {
    TickType_t xLastWakeTime = xTaskGetTickCount();
    const TickType_t xFrequency = pdMS_TO_TICKS(10); // 100Hz = 10ms period

    for (;;) {
        // 1. Parse GPS Data (Non-blocking)
        GPS_PollData();
        
        // 2. Read Stable IMU2 (Free Surface)
        Vector3 accel = IMU2_ReadAccel();
        Vector3 gyro = IMU2_ReadGyro();
        
        // 3. Run Error-State Kalman Filter (INS + GPS Fusion)
        navigator.update(accel, gyro, GPS_GetPosition(), GPS_GetHDOP());
        
        // 4. Calculate Steering Commands based on trajectory deviation
        Vector3 steer_cmd = navigator.calculate_canard_deflection();
        
        // 5. Send steering commands across Slip Rings to Canard Actuators
        CanardActuators_SetDeflection(steer_cmd);

        // Block until next 10ms tick
        vTaskDelayUntil(&xLastWakeTime, xFrequency);
    }
}