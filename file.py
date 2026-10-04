import os

# Define the directory structure and files
project_structure = {
    "Core/Src": ["main.c", "stm32f4xx_hal_msp.c", "stm32f4xx_it.c", "system_stm32f4xx.c"],
    "Core/Inc": ["main.h", "stm32f4xx_hal_conf.h", "stm32f4xx_it.h"],
    "App/Tasks": ["Task_Despin.cpp", "Task_Despin.hpp", "Task_Navigation.cpp", "Task_Navigation.hpp", 
                  "Task_Fuze.cpp", "Task_Fuze.hpp", "Task_Comms.cpp", "Task_Comms.hpp"],
    "App/Algorithms": ["DespinController.cpp", "DespinController.hpp", "INS_Mechanization.cpp", 
                       "INS_Mechanization.hpp", "GuidanceFusion.cpp", "GuidanceFusion.hpp", 
                       "FuzeLogic.cpp", "FuzeLogic.hpp", "MathTypes.hpp"],
    "App/Hardware": ["SlipRing_Interface.cpp", "SlipRing_Interface.hpp", "InductiveProgrammer.cpp", 
                     "InductiveProgrammer.hpp", "CanardActuators.cpp", "CanardActuators.hpp"],
    "App/Config": ["AstraConfig.hpp", "PinMappings.hpp"],
    "Drivers/IMU": ["IMU1_SpinRate.cpp", "IMU2_StableNav.cpp", "IMU_Common.hpp"],
    "Drivers/GPS": ["GPS_Receiver.cpp", "GPS_Receiver.hpp"],
    "Drivers/Sensors": ["HighG_Accel.cpp", "Barometer.cpp"],
    "Drivers/Power": ["PowerManagement.cpp"],
    "Middlewares/FreeRTOS/include": [],
    "Middlewares/FreeRTOS/portable": [],
    "Middlewares/CMSIS_DSP/Include": [],
    "Middlewares/CMSIS_DSP/Lib": [],
    "Build": [".gitkeep"]
}

# Create directories and files
for directory, files in project_structure.items():
    os.makedirs(directory, exist_ok=True)
    for file in files:
        file_path = os.path.join(directory, file)
        if not os.path.exists(file_path):
            with open(file_path, 'w') as f:
                f.write(f"// File: {file}\n// Auto-generated for ASTRA-PGK Firmware\n")
            print(f"Created: {file_path}")

# Create root files
root_files = ["CMakeLists.txt", "STM32F4xx.ld"]
for file in root_files:
    with open(file, 'w') as f:
        f.write(f"// {file}\n")
    print(f"Created: {file}")

print("\nASTRA-PGK Project Structure successfully generated!")