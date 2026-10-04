#pragma once
#include <cstdint>

// Optimized for ARM Cortex-M4F FPU
struct Vector3 {
    float x, y, z;
    Vector3() : x(0), y(0), z(0) {}
    Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
};

struct Matrix3x3 {
    float m[3][3];
    Matrix3x3() { for(int i=0; i<3; ++i) for(int j=0; j<3; ++j) m[i][j] = (i==j) ? 1.0f : 0.0f; }
};

struct TargetData {
    float lat, lon, alt;
    uint32_t time_of_impact_ms;
    float muzzle_velocity;
    uint8_t fuze_mode; // 0: Impact, 1: Proximity, 2: Timer
};