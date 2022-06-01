# M5Stack DDT M06/M15 Library

中国Direct Drive Tech社製ダイレクトドライブモーター用のArduinoライブラリです。

販売ページ(スイッチサイエンス):  <https://www.switch-science.com/catalog/7646/>

M5Stack,M5SickC用を想定していますが、送受信部分のコードを一部可変すれば他のArduinoボードでも動作するかと思います。

## Hardware

- M5 series
- [RS485ユニット](https://www.switch-science.com/catalog/6554/) ([Hat](https://www.switch-science.com/catalog/6472/)でも可)

結線に関してはデータシート参照

## Usage

### Spin the motor

```c
 Control_Motor(uint16_t Speed, uint8_t ID, uint8_t Acce, uint8_t Brake_P, Receiver *Receiver);
 ```

それぞれのモードにおいても、第一引数のSpeedに値を入れます。

Acceleration：Valid in velocity loop. unity: RPM/0.1ms. When set to 0, it wouldbethe default value

Brake：Valid in velocity loop when the value is 0XFF. Brake won’t work at other
values.

Receiver

- Receiv.BMode
- Receiv.ECurru
- Receiv.BSpeed
- Receiv.Position
- Receiv.ErrCode

### Obtain other feedback

```c
Get_Motor(uint8_t ID, Receiver *Receiver);
```

Receiver

- Receiv.BMode
- Receiv.ECurru
- Receiv.BSpeed
- Receiv.Temp
- Receiv.Position
- Receiv.ErrCode

Angle in 8 bits：0~256 corresponds to 0~360° Stator

temperature ：unity : ℃

### Mode switching

```c
Set_MotorMode(uint8_t Mode, uint8_t ID);
```

| Mode | Value |  |
|:-------------------|----------:|:------------------------------:|
| **Current Mode**   | 0x01      | -32767~32767 correspond to 0~8A|
| **Velocity Mode**  | 0x02      | -330~330 rpm                   |
| **Angle Mode**     | 0x03      | 0~32767correspond to 0°~360°   |

Only when the velocity is lower than 10 rpm that switching to angle loopisavailable.

### ID setting

```c
Set_MotorID(uint8_t ID);
```

Note：When setting the ID, please make sure that the bus has only one motor.

ID setting is allowed once every power reset. The ID will be changed after 5 times repeating the ID setting command.

### ID check

```c
Check_Motor(Receiver *Receiver);
```

Note: When checking the ID, please make sure that the bus has only one moto

## Author

[ゆうもや](https://twitter.com/takex5g)

## Reference

- [HarvestX - DDT-M0601C-112-U2D2](https://github.com/HarvestX/DDT-M0601C-112-U2D2)

- [Direct Drive Tech - Sample Code](https://github.com/Direcrt-Drive-Technology/M15-M06motor_Samplecode/tree/main/M0602C_Samplecode)
