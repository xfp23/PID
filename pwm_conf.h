#ifndef PWM_CONF_H
#define PWM_CONF_H

#include <Arduino.h>
//四个电机刚开机的控制duty
#define START_PWM_1  200//电机起始pwm占空比
#define START_PWM_2  200
#define START_PWM_3  255
#define START_PWM_4  100

#define DELAY_MS(S) vTaskDelay(S / portTICK_PERIOD_MS)//毫秒级延时
#define DELAY_US(S) vTaskDelay((S / 1000) / portTICK_PERIOD_MS) // 延时（微秒级）
 
//最大占空比
#define MAX1_DUTY  255 /*调试得出*/
#define MIN1_DUTY  180/*调试得出*/
#define MAX2_DUTY  255 /*调试得出*/
#define MIN2_DUTY  190/*调试得出*/
#define MAX3_DUTY  255 /*调试得出*/
#define MIN3_DUTY  180  /*调试得出*/



#define M1_CHANNEL 0
#define M2_CHANNEL 1
#define M3_CHANNEL 2
#define M4_CHANNEL 3

#define __LOW(PIN) digitalWrite(PIN,LOW)
#define __HIGH(PIN) digitalWrite(PIN,HGIG)

#define FREQ 5000
#define RESOLUTION_BITS 8

struct MOTORSPEED {
    unsigned int M1_PWM_OUT;
    unsigned int M2_PWM_OUT;
};
#endif
