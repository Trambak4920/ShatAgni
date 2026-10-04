#ifndef DESPINCONTROLLER_HPP
#define DESPINCONTROLLER_HPP

class DespinController {
private:
    float Kp, Kd;
    float prev_error;
public:
    DespinController(float p, float d);
    float calculate(float current_spin_rate, float target_spin_rate);
};

#endif