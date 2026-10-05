#pragma once
#include "MathTypes.hpp"
class INS_Mechanization {
public:
    Vector3 position, velocity;
    float roll, pitch, yaw;
    INS_Mechanization() : roll(0), pitch(0), yaw(0) {}
    void propagate(Vector3 accel, Vector3 gyro, float dt);
};
