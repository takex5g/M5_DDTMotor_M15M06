#include <DDT_Motor_M15M06.h>
#include <M5StickCPlus.h>

uint8_t Acce = 0;    // Acceleration of motor
uint8_t Brake_P = 0; // Brake position of motor
uint8_t ID = 1;      // ID of Motor (default:1)

Receiver Receiv;
// M5Stackのモジュールによって対応するRX,TXのピン番号が違うためM5製品とRS485モジュールに対応させてください
auto motor_handler = MotorHandler(33, 32); // RX,TX

void setup()
{
  Serial.begin(115200);
  Serial.println("DDT-Motor RS485");
  delay(100);
  motor_handler.Control_Motor(0, ID, Acce, Brake_P, &Receiv); //モータ停止
  delay(100);
  uint8_t Mode = 0x03;                   // angle loop
  motor_handler.Set_MotorMode(Mode, ID); //モード変更
  delay(100);
}

void loop()
{
  while (true)
  {
    setAngle(0);
    delay(4000);
    setAngle(32767 / 2);
    delay(4000);
    setAngle(32767);
    delay(4000);
    setAngle(32767 / 2);
    delay(4000);
  }
}
void setAngle(uint16_t Angle)
{

  motor_handler.Control_Motor(Angle, ID, Acce, Brake_P, &Receiv);
  Serial.print("Mode:");
  Serial.print(Receiv.BMode);
  Serial.print(" Position:");
  Serial.print(Receiv.Position);
  Serial.print(" inputAngle:");
  Serial.println(Angle);
}
