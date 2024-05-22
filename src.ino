#include "pins.h"
#include <Wire.h>
#include "pwm_conf.h"

extern void update_PID();
extern void pwm_Application(void *param);
extern void PID_Application(void *param);
extern void mpu_Application(void *param);
extern void PID_loop();
extern void mpu6050_loop();
extern void init_mpu6050();
extern void init_pwm();
//extern void init_pid();
extern void pwm_loop();
extern void update_pwm();
extern void init_screen();
extern void screen_loop();
extern void screen_Application(void *param);

void setup()
{
      pinMode(MOTOR1_A_PIN, OUTPUT);
    pinMode(MOTOR1_B_PIN, OUTPUT);
    pinMode(MOTOR2_A_PIN, OUTPUT);
     pinMode(MOTOR2_B_PIN, OUTPUT);
    Serial.begin(115200);
    Serial.println("start");
     init_screen();
      xTaskCreate(screen_Application,"screen",4096,NULL,1,NULL);
     init_mpu6050();
     //update_PID();

     init_pwm();

  
   
    xTaskCreate(pwm_Application,"pwm",4096,NULL,3,NULL);
    xTaskCreate(mpu_Application,"mpu",4096,NULL,10,NULL);
   xTaskCreate(PID_Application,"PID",8012,NULL,7,NULL);
    Serial.println("task has been create!");
    
}

void loop()
{
  //update_PID();
  
}
