#pragma once
#include <cstdint>
class FuzeLogic {
private:
    uint32_t target_time_ms;
    bool sa_armed;
public:
    FuzeLogic();
    void arm_safety_and_arming(float current_spin_rate);
    bool check_impact(float accel_g);
    bool check_proximity(float pressure_pa);
    bool check_timer(uint32_t current_time_ms);
};
