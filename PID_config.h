#ifndef PID_CONFIG_H
#define PID_CONFIG_H

struct PIDCTROL {
    float Input;
     float Output;
     float  Setpoint; // 输入，输出，目标姿态角度
     float kp;
     float ki;
     float kd;

};

#endif
