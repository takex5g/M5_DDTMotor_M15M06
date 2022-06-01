#include "DDT_Motor_M15M06.h"

MotorHandler::MotorHandler(int RX, int TX)
{
	// Baud rate：115200 Data bit：8bit Stop bit：1bit Parity check：none
	Serial2.begin(115200, SERIAL_8N1, RX, TX);
}

void MotorHandler::Control_Motor(uint16_t Speed, uint8_t ID, uint8_t Acce, uint8_t Brake_P, Receiver *Receiver)
{
	this->Tx[0] = ID;
	this->Tx[1] = 0x64;
	this->Tx[2] = Speed >> 8;
	this->Tx[3] = Speed & 0x00ff;
	this->Tx[4] = 0;
	this->Tx[5] = 0;
	this->Tx[6] = Acce;
	this->Tx[7] = Brake_P;
	this->Tx[8] = 0;
	this->Tx[9] = CRC8_Table(Tx.data(), 9);
	Send_Motor();

	Receive_Motor();
	Receiver->ID = this->Rx[0];
	Receiver->BMode = this->Rx[1];
	Receiver->ECurru = (this->Rx[2] << 8) + this->Rx[3];
	Receiver->BSpeed = (this->Rx[4] << 8) + this->Rx[5];
	Receiver->Position = (this->Rx[6] << 8) + this->Rx[7];
	Receiver->ErrCode = this->Rx[8];
}

void MotorHandler::Get_Motor(uint8_t ID, Receiver *Receiver)
{
	Tx[0] = ID;
	Tx[1] = 0x74;
	Tx[2] = 0;
	Tx[3] = 0;
	Tx[4] = 0;
	Tx[5] = 0;
	Tx[6] = 0;
	Tx[7] = 0;
	Tx[8] = 0;
	Tx[9] = CRC8_Table(Tx.data(), 9);
	Send_Motor();

	Receive_Motor();
	Receiver->ID = Rx[0];
	Receiver->BMode = Rx[1];
	Receiver->ECurru = (Rx[2] << 8) + Rx[3];
	Receiver->BSpeed = (Rx[4] << 8) + Rx[5];
	Receiver->Temp = Rx[6];
	Receiver->Position = Rx[7];
	Receiver->ErrCode = Rx[8];
}

void MotorHandler::Set_MotorMode(uint8_t Mode, uint8_t ID)
{
	Tx[0] = ID;
	Tx[1] = 0xA0;
	Tx[2] = 0;
	Tx[3] = 0;
	Tx[4] = 0;
	Tx[5] = 0;
	Tx[6] = 0;
	Tx[7] = 0;
	Tx[8] = 0;
	Tx[9] = Mode;
	Send_Motor();
}

void MotorHandler::Set_MotorID(uint8_t ID)
{
	Tx[0] = 0xAA;
	Tx[1] = 0x55;
	Tx[2] = 0x53;
	Tx[3] = ID;
	Tx[4] = 0;
	Tx[5] = 0;
	Tx[6] = 0;
	Tx[7] = 0;
	Tx[8] = 0;
	Tx[9] = 0;
	Send_Motor();
}

void MotorHandler::Check_Motor(Receiver *Receiver)
{
	Tx[0] = 0xc8;
	Tx[1] = 0x64;
	Tx[2] = 0;
	Tx[3] = 0;
	Tx[4] = 0;
	Tx[5] = 0;
	Tx[6] = 0;
	Tx[7] = 0;
	Tx[8] = 0;
	Tx[9] = CRC8_Table(Tx.data(), 9);

	Send_Motor();
	Receive_Motor();

	Receiver->ID = Rx[0];
	Receiver->BMode = Rx[1];
	Receiver->ECurru = (Rx[2] << 8) + Rx[3];
	Receiver->BSpeed = (Rx[4] << 8) + Rx[5];
	Receiver->Position = (Rx[6] << 8) + Rx[7];
	Receiver->ErrCode = Rx[8];
}

void MotorHandler::Send_Motor()
{
	Serial2.write(Tx.data(), 10);
}

void MotorHandler::Receive_Motor()
{
	if (Serial2.available())
	{
		Serial2.readBytes(Rx.data(), 10);
	}
}

unsigned char MotorHandler::CRC8_Table(uint8_t *p, int counter)
{
	unsigned char crc8 = 0;
	// Model:CRC-8/MAXIM
	// polynomial x8 + x5 + x4 + 1

	for (; counter > 0; counter--)
	{
		crc8 = CRC8Table[crc8 ^ *p];
		p++;
	}
	return (crc8);
}
