#include "DespinController.hpp"

DespinController::DespinController(float p, float d) : Kp(p), Kd(d), prev_error(0.0f) {}

float DespinController::calculate(float current_spin_rate, float target_spin_rate) {
    float error = target_spin_rate - current_spin_rate;
    
    // PD Control (Integral omitted to prevent windup during 15,000G launch shock)
    float derivative = error - prev_error;
    prev_error = error;
    
    float control_signal = (Kp * error) + (Kd * derivative);
    
    // Clamp to PWM limits (0.0 to 1.0)
    if (control_signal > 1.0f) return 1.0f;
    if (control_signal < -1.0f) return -1.0f;
    
    return control_signal;
}