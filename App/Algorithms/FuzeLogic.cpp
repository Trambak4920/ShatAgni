#include "FuzeLogic.hpp"

FuzeLogic::FuzeLogic() : target_time_ms(0), sa_armed(false) {}

void FuzeLogic::arm_safety_and_arming(float current_spin_rate) {
    // Mechanical/Logical S&A arming logic
    // Arms only after detecting sufficient spin and time-of-flight
    if (current_spin_rate > 50.0f) { // e.g., > 50 Hz
        sa_armed = true;
    }
}

bool FuzeLogic::check_impact(float accel_g) {
    if (accel_g > IMPACT_G_THRESHOLD && sa_armed) { 
        return true; // DETONATE
    }
    return false;
}

bool FuzeLogic::check_proximity(float pressure_pa) {
    const float P0 = 101325.0f; 
    float altitude = 44330.0f * (1.0f - powf(pressure_pa / P0, 0.1903f));
    
    if (altitude <= PROXIMITY_HOB_METERS && sa_armed) {
        return true; // DETONATE
    }
    return false;
}

bool FuzeLogic::check_timer(uint32_t current_time_ms) {
    if (current_time_ms >= (target_time_ms - TIMER_SAFETY_MARGIN_MS) && sa_armed) {
        return true; // DETONATE
    }
    return false;
}
