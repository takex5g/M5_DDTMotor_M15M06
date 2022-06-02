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
  Serial.println("DDT-Motor RS485");

  motor_handler.Control_Motor(0, ID, Acce, Brake_P, &Receiv);
}

const int16_t SPEED_MAX = 330;
const int16_t SPEED_MIN = -330;
void loop()
{
  while (true)
  {
    Speed++;
    delay(5);
    motor_handler.Control_Motor(Speed, ID, Acce, Brake_P, &Receiv);
    Serial.print(" Mode:");
    Serial.print(Receiv.BMode);
    Serial.print(" Speed:");
    Serial.println(Receiv.BSpeed);
    if (Speed > int16_t(SPEED_MAX))
    {
      break;
    }
  }

  while (true)
  {
    Speed--;
    delay(5);
    motor_handler.Control_Motor(Speed, ID, Acce, Brake_P, &Receiv);
    Serial.print(" Mode:");
    Serial.print(Receiv.BMode);
    Serial.print(" Speed:");
    Serial.println(Receiv.BSpeed);
    if (Speed < SPEED_MIN)
    {
      break;
    }
  }
}
