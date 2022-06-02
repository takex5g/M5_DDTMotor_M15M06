/*
 *回転を行いながらモータの状態を取得するサンプル
 */
#include <DDT_Motor_M15M06.h>
#include <M5StickCPlus.h>

int16_t Speed = 0;   // Speed of motor
uint8_t Acce = 0;    // Acceleration of motor
uint8_t Brake_P = 0; // Brake position of motor
uint8_t ID = 1;      // ID of Motor (default:1)

Receiver Receiv;
// M5Stackのモジュールによって対応するRX,TXのピン番号が違うためM5製品とRS485モジュールに対応させてください
auto motor_handler = MotorHandler(33, 32); // RX,TX

void setup()
{
  Serial.begin(115200);
  Serial.println("DDT-Motor get_motor_feedback");
}

const int16_t SPEED_MAX = 330;
const int16_t SPEED_MIN = -330;
void loop()
{
  while (true)
  {
    Speed++;
    spin_and_get(Speed);
    if (Speed > int16_t(SPEED_MAX))
    {
      break;
    }
  }

  while (true)
  {
    Speed--;
    spin_and_get(Speed);
    if (Speed < SPEED_MIN)
    {
      break;
    }
  }
}
void spin_and_get(int16_t _Speed)
{
  motor_handler.Control_Motor(_Speed, ID, Acce, Brake_P, &Receiv);
  delay(10);
  //温度を取得したい場合はGet_Motor関数を呼び出す
  motor_handler.Get_Motor(ID, &Receiv);
  delay(10);
  Serial.print("ID:");
  Serial.print(Receiv.ID);
  Serial.print(" Mode:");
  Serial.print(Receiv.BMode);
  Serial.print(" Current:");
  Serial.print(Receiv.ECurru);
  Serial.print(" Speed:");
  Serial.print(Receiv.BSpeed);
  Serial.print(" Position:");
  Serial.print(Receiv.Position);
  Serial.print(" Tmp:");
  Serial.print(Receiv.Temp);
  Serial.print(" ErrCode:");
  Serial.println(Receiv.ErrCode);
}
