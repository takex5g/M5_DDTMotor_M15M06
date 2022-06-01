#include <DDT_Motor_M15M06.h>
#include <M5StickCPlus.h>

Receiver Receiv;

// M5StackのモジュールによってRX,TXのピン番号は違います
auto motor_handler = MotorHandler(33, 32); // RX,TX
void setup()
{
  Serial.begin(115200);
  Serial.println("Mode switching:");
}

void loop()
{
  // mode：
  // 0x01 ：Current loop
  // 0x02 ：Velocity loop
  // 0x03 ：Angle loop
  // Only when the velocity is lower than 10 rpm that switching to angle loopisavailable.

  uint8_t ID = 0x01;
  uint8_t Mode = 0x02; // Velocity loop

  //現在のモード
  motor_handler.Get_Motor(ID, &Receiv);
  Serial.print("current mode:");
  Serial.println(Receiv.BMode);
  delay(500);

  //変更
  motor_handler.Set_MotorMode(Mode, ID);
  Serial.println("switched");

  delay(500);

  //変更後のモード
  motor_handler.Get_Motor(ID, &Receiv);
  Serial.print("mode:");
  Serial.println(Receiv.BMode);
  delay(5000);
}
