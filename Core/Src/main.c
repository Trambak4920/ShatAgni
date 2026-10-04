#include "main.h"
#include "FreeRTOS.h"
#include "task.h"

// Forward declarations of C++ Tasks (wrapped in extern "C" to link with C main)
extern void StartDespinTask(void *argument);
extern void StartNavigationTask(void *argument);
extern void StartFuzeTask(void *argument);
extern void StartCommsTask(void *argument);

int main(void)
{
    HAL_Init();
    SystemClock_Config(); // Configure STM32F4 to 168MHz
    MX_GPIO_Init();
    MX_SPI1_Init(); // For IMUs
    MX_USART2_UART_Init(); // For GPS
    MX_TIM2_Init(); // For PWM/Canards

    // Create FreeRTOS Tasks
    xTaskCreate(StartDespinTask, "Despin", 256, NULL, 5, NULL);       // Highest Priority
    xTaskCreate(StartFuzeTask, "Fuze", 256, NULL, 4, NULL);           // High Priority (Safety)
    xTaskCreate(StartNavigationTask, "Nav", 512, NULL, 3, NULL);      // Medium Priority (Heavy Math)
    xTaskCreate(StartCommsTask, "Comms", 256, NULL, 1, NULL);         // Low Priority

    // Start Scheduler (Never returns)
    vTaskStartScheduler();

    while (1) {
        // Should never reach here
    }
}