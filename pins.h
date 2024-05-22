#ifndef PINS_H
#define PINS_H


#define MOTOR1_A_PIN 5
#define MOTOR1_B_PIN  4
#define MOTOR1_PWM_PIN 6


#define MOTOR2_A_PIN 1
#define MOTOR2_B_PIN 10
#define MOTOR2_PWM_PIN 0


#define SDA_PIN   3
#define SCL_PIN   2


//棧空间
#define STACK 4096

//mpu传感器数据
typedef struct{
    int ax;
    int ay;
    int az;
    double angle;//角速度
    int cx;
    int cy;
    int cz;
    double accgle;//加速度
}MUPD;

#endif
