cmake_minimum_required(VERSION 3.22)

# Project Definition
project(ASTRA_PGK_Firmware C CXX ASM)

# Compiler Settings
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_C_STANDARD 11)

# Toolchain (Assuming ARM GCC is installed)
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

# MCU Flags
set(MCU_FLAGS "-mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${MCU_FLAGS} -Wall -fdata-sections -ffunction-sections")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${MCU_FLAGS} -Wall -fdata-sections -ffunction-sections -fno-rtti -fno-exceptions")
set(CMAKE_EXE_LINKER_FLAGS "${MCU_FLAGS} -Wl,--gc-sections -T${CMAKE_SOURCE_DIR}/STM32F4xx.ld")

# Include Directories
include_directories(
    Core/Inc
    App/Tasks
    App/Algorithms
    App/Hardware
    App/Config
    Drivers/IMU
    Drivers/GPS
    Drivers/Sensors
    Drivers/Power
    Middlewares/FreeRTOS/include
    Middlewares/CMSIS_DSP/Include
)

# Source Files
file(GLOB_RECURSE SOURCES 
    "Core/Src/*.c"
    "App/Tasks/*.cpp"
    "App/Algorithms/*.cpp"
    "App/Hardware/*.cpp"
    "Drivers/IMU/*.cpp"
    "Drivers/GPS/*.cpp"
    "Drivers/Sensors/*.cpp"
    "Drivers/Power/*.cpp"
)

# Executable
add_executable(${PROJECT_NAME}.elf ${SOURCES})

# Post-build to generate .bin and .hex
add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:${PROJECT_NAME}.elf> ${PROJECT_NAME}.hex
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${PROJECT_NAME}.elf> ${PROJECT_NAME}.bin
)
