#include <MPU6050_tockn.h>
#include <Wire.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "pins.h"
#include "math.h"
#include "pwm_conf.h"
//存储了传感器数据，需要扩展到pid模块
volatile MUPD mpu_data;
unsigned long timer=0;


MPU6050 mpu6050(Wire);
void init_mpu6050()
{
    Wire.begin(SDA_PIN,SCL_PIN);
    mpu6050.begin();
    mpu6050.calcGyroOffsets(true);

}

void mpu6050_loop()
{
   mpu6050.update();
   if(millis()-timer>1000){
    mpu_data.cx=mpu6050.getAccX();
    mpu_data.cy=mpu6050.getAccY();
    mpu_data.cz=mpu6050.getAccZ();
    //求出加速度
    mpu_data.accgle=sqrt(pow(mpu_data.cx,2))+sqrt(pow(mpu_data.cy,2))+sqrt(pow(mpu_data.cz,2));

    mpu_data.ax=mpu6050.getAccAngleX();
    mpu_data.ay=mpu6050.getAccAngleY();
    //求出角速度
    mpu_data.angle=(mpu_data.ax+mpu_data.ay)/2;
    timer=millis();
   }
}

void mpu_Application(void *param)
{
   
    while(true)
    {
      //static bool sta=true;
      mpu6050_loop();
      DELAY_MS(10);
    }

}
