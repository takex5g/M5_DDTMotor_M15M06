# M5Stack DDT Motor M06/M15 Library

中国Direct Drive Tech社製ダイレクトドライブモーターのArduinoライブラリです。

販売ページ(スイッチサイエンス):  <https://www.switch-science.com/catalog/7646/>

M5Stack,M5SickC等のM5シリーズでの使用を想定していますが、送受信部分のコードを一部可変すれば他のArduinoボードでも動作するかと思います。

## Hardware

- M5 Stack series
- [RS485ユニット](https://www.switch-science.com/catalog/6554/) ([Hat](https://www.switch-science.com/catalog/6472/)でも可)

結線に関してはデータシート参照

## Installing

1. githubで本リポジトリを.zipでダウンロード
2. ArduinoIDEから`スケッチ` ->  `ライブラリをインクルード` -> `.zip形式のライブラリをインストール`

## Usage

`ファイル` -> `スケッチ例` -> `DDT_Motor_M15M06` よりサンプルスケッチがあるのでそちらを参照してください。

- spin_the_motor.ino

   モーターの正転逆転を行いつつ、シリアルモニタに現在速度を出力


## Description

### Initialize

```c
auto motor_handler = MotorHandler(33, 32); // RX,TX
```

RX,TXはM5Stackの種類や使用しているモジュール・Hatによって異なります。

### Spin the motor

```c
 Control_Motor(uint16_t Speed, uint8_t ID, uint8_t Acce, uint8_t Brake_P, Receiver *Receiver);
 ```

いずれのモードにおいても、第一引数のSpeedに値を入れます。

Acceleration：Valid in velocity loop. unity: RPM/0.1ms. When set to 0, it wouldbethe default value

Brake：Valid in velocity loop when the value is 0xFF. Brake won’t work at other
values.

#### Receiverオブジェクトにモーターの状態が格納されます

- `Receiv.ID` ID
- `Receiv.BMode` モード(mode)
- `Receiv.ECurru` 電流(Current)
- `Receiv.BSpeed` 速度(Velocity)
- `Receiv.Position` 位置(Angle)
- `Receiv.ErrCode` エラーコード(Fault value)

### Obtain other feedback

```c
Get_Motor(uint8_t ID, Receiver *Receiver);
```

#### Receiverオブジェクトにモーターの状態が格納されます

- `Receiv.ID` ID
- `Receiv.BMode` モード(mode)
- `Receiv.ECurru` 電流(Current)
- `Receiv.BSpeed` 速度(Velocity)
- `Receiv.Temp` 温度(Stator tempe rature)
- `Receiv.Position` 位置(Angle)
- `Receiv.ErrCode` エラーコード(Fault value)

Angle in 8 bits：0 ~ 256 corresponds to 0 ~ 360° Stator

temperature ：unity : ℃

### Mode switching

```c
Set_MotorMode(uint8_t Mode, uint8_t ID);
```

| Mode | Value |  |
|:-------------------|----------:|:------------------------------:|
| **Current Mode**   | 0x01      | -32767 ~ 32767 correspond to 0 ~ 8A，INT16|
| **Velocity Mode**  | 0x02      | -330~330 rpm，INT16                   |
| **Angle Mode**     | 0x03      | 0 ~ 32767correspond to 0° ~ 360°，UNT16|

Only when the velocity is lower than 10 rpm that switching to angle loopisavailable.
モード変更はフラッシュには保存されません。

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

Note: When checking the ID, please make sure that the bus has only one motor

### Error Code

| Fault value |  BIT7  | BIT6   | BIT5   | BIT4   | BIT3 | BIT2 | BIT1 | BIT0 |
|:------------|-------:|:------:|:------:|:------:|:----:|:----:|:----:|:----:|
|Description  |Reserved|Reserved|Reserved|Overheat|Stall|Phase Over current|Bus over current|Sensor Fault|

Sensor Fault
E.g.：0x02 or 0b00000010 corresponds to Bus over current.

## Trouble Shooting

- コマンドを送っているのにモーターが回らない/値が取得できない
  - 一度モーターの電源を切り、再度電源投入すると値が取れる場合がある
  - モーターのケーブル黒線はGNDではないので注意
  - デフォルトIDは0ではなく0x01, Velocity Mode

## Author

[ゆうもや](https://twitter.com/takex5g)

## Reference

- [HarvestX - DDT-M0601C-112-U2D2](https://github.com/HarvestX/DDT-M0601C-112-U2D2)

- [Direct Drive Tech - Sample Code](https://github.com/Direcrt-Drive-Technology/M15-M06motor_Samplecode/tree/main/M0602C_Samplecode)
