#pragma once

// De-Spid PID Gains
#define DESPIN_KP 2.5f
#define DESPIN_KD 0.1f

// Navigation & Kalman Filter Covariances
#define KF_PROCESS_NOISE_Q 0.01f
#define KF_MEASUREMENT_NOISE_R_GPS 0.5f
#define KF_MEASUREMENT_NOISE_R_INS 0.05f

// Fuze Thresholds
#define IMPACT_G_THRESHOLD 800.0f   // High-G threshold for impact (in Gs)
#define PROXIMITY_HOB_METERS 15.0f  // Height of Burst for airburst
#define TIMER_SAFETY_MARGIN_MS 500  // Safety margin before programmed time

// Task Stack Sizes (Words)
#define STACK_DESPIN 256
#define STACK_NAV 512
#define STACK_FUZE 256
#define STACK_COMMS 256