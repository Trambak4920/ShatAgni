#include "Task_Despin.hpp"
#include "DespinController.hpp"
#include "IMU1_SpinRate.h"
#include "SlipRing_Interface.hpp"
#include "FreeRTOS.h"
#include "task.h"

// Instantiate the PID Controller
DespinController despid_ctrl(2.5f, 0.1f); 

extern "C" void StartDespinTask(void *argument) {
    TickType_t xLastWakeTime = xTaskGetTickCount();
    const TickType_t xFrequency = pdMS_TO_TICKS(1); // 1kHz = 1ms period

    for (;;) {
        // 1. Read high spin rate from IMU1 (Spinning Body)
        float current_spin_rate = IMU1_ReadRollRate(); // Returns rad/s
        
        // 2. Calculate required counter-torque (Target is 0 rad/s)
        float motor_pwm = despid_ctrl.calculate(current_spin_rate, 0.0f);
        
        // 3. Send command across Tungsten Slip Rings to the free surface actuators
        SlipRing_SendMotorCommand(motor_pwm);

        // Block until next 1ms tick
        vTaskDelayUntil(&xLastWakeTime, xFrequency);
    }
}