#include <DDT_Motor_M15M06.h>
#include <M5StickCPlus.h>

Receiver Receiv;

// M5StackのモジュールによってRX,TXのピン番号は違います
auto motor_handler = MotorHandler(33, 32); // RX,TX
void setup()
{
  Serial.begin(115200);
  Serial.println("ID setting");
  //モーターIDを2に変更するサンプル
  uint8_t ID = 2;
  for (int i = 0; i < 5; i++)
  {
    motor_handler.Set_MotorID(ID);
    delay(500);
  }
  Serial.println("setted");
  // Note：When setting the ID, please make sure that the bus has only one motor. ID setting is allowed once every power reset.
}

void loop()
{
}
