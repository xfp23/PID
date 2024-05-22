#include "PidController.h"
#include "PID_config.h"
#include "pwm_conf.h"
#include "pins.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <MPU6050_tockn.h>


// 电机的输出结构
extern volatile struct MOTORSPEED Speed;

struct PIDCTROL M1_A = {
  .Input=0,
  .Output=0,
  .Setpoint=0,
  .kp=8,
  .ki=0.6,
  .kd=5,
};

struct PIDCTROL M2_A = {
  .Input=0,
  .Output=0,
  .Setpoint=0,
  .kp=8,
  .ki=0.6,
  .kd=5,
};
extern volatile MUPD mpu_data;

 PidController M1PID;
 PidController M2PID;

void init_pid()
{
  M1PID.update_pid(M1_A.kp, M1_A.ki, M1_A.kd);
  M1PID.update_target(M1_A.Setpoint);
  M1PID.out_limit(-255,255);
  M1PID.update(sqrt(pow(mpu_data.angle,2)));
  M2PID.update_pid(M2_A.kp, M2_A.ki, M2_A.kd);
  M2PID.update_target(M2_A.Setpoint);
  M2PID.out_limit(-255,255);
  M2PID.update(sqrt(pow(mpu_data.angle,2)));

}

void PID_loop()
{
  if(mpu_data.angle>=0)
  {
    digitalWrite(MOTOR1_A_PIN,HIGH);
    digitalWrite(MOTOR1_B_PIN,LOW);
    digitalWrite(MOTOR2_A_PIN,HIGH);
    digitalWrite(MOTOR2_B_PIN,LOW);

  }
  else {
    digitalWrite(MOTOR1_A_PIN,LOW);
    digitalWrite(MOTOR1_B_PIN,HIGH);
    digitalWrite(MOTOR2_A_PIN,LOW);
    digitalWrite(MOTOR2_B_PIN,HIGH);
  }
  Speed.M1_PWM_OUT= sqrt(pow((M1PID.update(mpu_data.angle))*5.14,2));
  Serial.println("pid:");
  Serial.print(M1PID.update(sqrt(pow(mpu_data.angle,2))));
  Speed.M2_PWM_OUT= sqrt(pow((M2PID.update(mpu_data.angle))*5.14,2));
}

void PID_Application(void *param) {
  (void)(param);

    while (true) {

        init_pid();
        PID_loop();
        DELAY_MS(10);
    }
}
