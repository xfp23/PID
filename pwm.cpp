#include <Arduino.h>
#include "pwm_conf.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "PID_config.h"
#include "pins.h"

/*传入蓝牙模块*/
extern volatile MUPD mpu_data;

 volatile struct MOTORSPEED  Speed={START_PWM_1,START_PWM_2};

void update_pwm() {
  if(Speed.M1_PWM_OUT>MAX1_DUTY)
  {
    Speed.M1_PWM_OUT=MAX1_DUTY;
  }
  else if (Speed.M1_PWM_OUT<MIN1_DUTY)
  {
    Speed.M1_PWM_OUT=MIN1_DUTY;
  }
    if(Speed.M2_PWM_OUT>MAX2_DUTY)
  {
    Speed.M2_PWM_OUT=MAX2_DUTY;
  }
  else if (Speed.M2_PWM_OUT<MIN2_DUTY)
  {
    Speed.M2_PWM_OUT=MIN2_DUTY;
  }
  Serial.println("SPEED :");
  Serial.print(Speed.M2_PWM_OUT);
  ledcWrite(M1_CHANNEL,Speed.M1_PWM_OUT);
  ledcWrite(M2_CHANNEL, Speed.M2_PWM_OUT);
  if(mpu_data.accgle>4)
  {
    while(1);
  }
  
}
void init_pwm()
{
  Serial.println("start pwm");
  digitalWrite(MOTOR1_A_PIN,HIGH);
  digitalWrite(MOTOR1_B_PIN,LOW);  
  digitalWrite(MOTOR2_A_PIN,HIGH);
  digitalWrite(MOTOR2_B_PIN,LOW);
  ledcSetup(M2_CHANNEL,FREQ,RESOLUTION_BITS);
  ledcAttachPin(MOTOR1_PWM_PIN,M1_CHANNEL);
  ledcAttachPin(MOTOR2_PWM_PIN,M2_CHANNEL);
}
void pwm_loop()
{
    update_pwm();
    Serial.println("pwm output success");
}
void pwm_Application(void * param)
{
  init_pwm();
   // (void)param;
    while (true)
    {
        update_pwm();
        
    }
}
