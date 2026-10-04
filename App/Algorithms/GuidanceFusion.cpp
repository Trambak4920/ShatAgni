#include "GuidanceFusion.hpp"
#include "arm_math.h" // CMSIS-DSP for matrix math

GuidanceFusion::GuidanceFusion() {
    // Initialize Covariance Matrix (High initial uncertainty)
    P[0][0] = 100.0f; P[1][1] = 100.0f; P[2][2] = 100.0f;
}

bool GuidanceFusion::isGPSViable(float hdop) {
    // If GPS HDOP is > 5.0 (poor signal/jammed), reject it
    if (hdop > 5.0f) return false;
    
    // If INS covariance (uncertainty) has grown too large, we MUST use GPS
    float trace_P = P[0][0] + P[1][1] + P[2][2];
    if (trace_P > 500.0f) return true; 
    
    return true; // Default viable
}

void GuidanceFusion::update(Vector3 accel, Vector3 gyro, Vector3 gps_pos, float hdop) {
    // 1. INS Prediction Step (Dead Reckoning using Stable IMU2)
    ins.propagate(accel, gyro, 0.01f); 
    
    // 2. Predict Covariance (P = F*P*F' + Q)
    // ... [CMSIS-DSP Matrix Multiplication goes here] ...

    // 3. GPS Measurement Step (Only if viable)
    if (isGPSViable(hdop)) {
        Vector3 innovation = {
            gps_pos.x - ins.position.x,
            gps_pos.y - ins.position.y,
            gps_pos.z - ins.position.z
        };
        
        // Kalman Gain Calculation (K = P*H' * (H*P*H' + R)^-1)
        // ... [CMSIS-DSP Matrix Inverse goes here] ...
        
        // Update INS Position
        ins.position.x += K[0][0] * innovation.x;
        ins.position.y += K[1][1] * innovation.y;
        ins.position.z += K[2][2] * innovation.z;
    } 
    // If GPS is denied, it relies purely on ins.propagate() (Closed-loop dead reckoning)
}