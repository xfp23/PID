/*#if defined(ESP32)

#include "BluetoothSerial.h"
#include "PID_config.h"
#include "pins.h"
#include "pwm_conf.h"



BluetoothSerial PIDBT; 

extern struct PIDCTROL M1_A;
extern struct PIDCTROL M2_A;
void init_ble()
{
  PIDBT.begin("PIDBT");
}

void  bt_debug() // 串口调试及控制函数
{
  if (PIDBT.available() > 0)
  {
    char DATA = PIDBT.read();
    DELAY_MS(2);
    switch (DATA)
    {
    case 'a':
      M1_A.kp += 0.1;
      break;
    case 'b':
      M1_A.ki += 0.1;
      break;
    case 'c':
      M1_A.kd += 0.1;
      break;
    case 'd':
      M1_A.Setpoint += 0.1;
      break;
    case '0':
    M2_A.kp += 0.1;
    break;
        case '1':
      M2_A.ki += 0.1;
      break;
    case '2':
      M2_A.kd += 0.1;
      break;
    case '3':
      M2_A.Setpoint += 0.1;
      break;
  }
}}

void BT_Application(void *param)
{
  (void)(param);
  while(true)
  {
    bt_debug();
  }
  
}
#endif*/