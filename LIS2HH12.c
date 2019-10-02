/*
 * LIS2HH12.c
 *
 *  Created on: 13/09/2019
 *      Author: manuelposada
 *
 *
 */

#include "Drivers_Hd/LIS2HH12.h"
/*
 ** ===================================================================
 **	  @brief  write a data in the indicated register
 **
 **	  @param  Reg Register to write
 **	  @param  data data to send.
 ** ===================================================================
*/
void LIS2HH12_Write(LIS2HH12_t *Obj, uint8_t Reg, uint8_t data) {
	uint8_t buffer[2];
	buffer[0] = Reg;
	buffer[1] = data;
	Obj->Write(Obj->Address, (void*)buffer, 2);
}
/*
 ** ===================================================================
 **	  @brief  Read the status of the indicated record
 **
 **	  @param  Reg Register to Read
 **	  @return value of register.
 ** ===================================================================
*/
uint8_t LIS2HH12_Read(LIS2HH12_t *Obj, uint8_t Reg ) {
	uint8_t buffer[2];
	buffer[0] = Reg;
	Obj->Read(Obj->Address, buffer, 1);
	return buffer[0];
}
/*
 ** ===================================================================
 **	  @brief  initiate the library
 **
 **	  @param  Write Wrapper to function
 **	  @param  Read Wrapper to function
 **	  @Addres_Device Address of the device
 ** ===================================================================
*/
void LIS2HH12_Init(LIS2HH12_t *Obj, Write_Fcn Write, Read_Fcn Read, uint8_t Addres_Device) {
	Obj->Write = Write;
	Obj->Read = Read;
	Obj->Address = Addres_Device;
}
/*
 ** ===================================================================
 **	  @brief  Who Am I
 ** ===================================================================
*/
uint8_t LIS2HH12_Who_Am_I(LIS2HH12_t *Obj) {
	return LIS2HH12_Read(Obj, WHO_AM_I);
}

/*
 ** ===================================================================
 **	  @brief Power Down Mode, edit the bits of the ODR register to
 **	  lower the frequency and enter low power mode
 ** ===================================================================
*/
void LIS2HH12_PowerDown_Mode(LIS2HH12_t *Obj) {
	uint8_t data;
	data = LIS2HH12_Read(Obj, CTRL_REG1);
	LIS2HH12_Write(Obj, CTRL_REG1, (data & ~_ODR_MASK));
}
/*
 ** ===================================================================
 **	  @brief Active Mode edit the bits of the ODR register to configure
 **	  the frequency with which you want to work
 **
 **	  @param Frecuency macros -> ODR_10HZ, ODR_50HZ, ODR_100HZ, ODR_200HZ,
 **	  ODR_400HZ, ODR_800HZ
 ** ===================================================================
*/
void LIS2HH12_Active_Mode(LIS2HH12_t *Obj, uint8_t Frecuency) {
	uint8_t data;
	data = LIS2HH12_Read(Obj, CTRL_REG1);
	LIS2HH12_Write(Obj, CTRL_REG1, (data & ~_ODR_MASK) | Frecuency);
}
/*
 ** ===================================================================
 **	  @brief  The BDU bit is used to inhibit the update of the output registers
 **	  until both upper and lower register parts are read
 **	  (BDU = ‘0’) the output register values are updated continuously
 **	  (BDU = ‘1’), the content of the output registers is not updated until
 **	  both MSB and LSB are read which avoids reading values related to
 **	  different sample times.
 **
 **	  @param BDU_ON_0FF macros LIS2HH12_ON or LIS2HH12_OFF depending on
 **	  whether the bit is turned off or on
 ** ===================================================================
*/
void LIS2HH12_Update_BDU(LIS2HH12_t *Obj, uint8_t BDU_ON_OFF) {
	uint8_t data;
	data = LIS2HH12_Read(Obj, CTRL_REG1);
	if(BDU_ON_OFF) LIS2HH12_Write(Obj, CTRL_REG1, (data | BDU));
	else  LIS2HH12_Write(Obj, CTRL_REG1, (data & ~BDU));
}
/*
 ** ===================================================================
 **	  @brief The measured acceleration data are sent to the OUT_X_H, OUT_X_L,
 **	  OUT_Y_H, OUT_Y_L, OUT_Z_H, and OUT_Z_L registers. These registers contain,
 **	  respectively, the most significant part and the least significant part of
 **	  the acceleration signals acting on the X, Y, and Z axes.
 **
 **	  @param Data 16-bit integer buffer in which the 3-axis accelerations
 **	  will be stored
 ** ===================================================================
*/
void LIS2HH12_ReadXYZ(LIS2HH12_t *Obj, int16_t *Data ) {
	uint8_t Buffer[8];
	Buffer[0] = OUT_X_L;
	Obj->Read(Obj->Address, Buffer, 6);
	Data[0] = (int16_t)Buffer[1] << 8 | Buffer[0];
	Data[1] = (int16_t)Buffer[3] << 8 | Buffer[2];
	Data[2] = (int16_t)Buffer[5] << 8 | Buffer[4];
}

/*
 ** ===================================================================
 **	  @brief
 ** ===================================================================
*/

void LIS2HH12_Full_Scale(LIS2HH12_t *Obj, uint8_t Full_Scale) {
	uint8_t data;
	data = LIS2HH12_Read(Obj, CTRL_REG4);
	LIS2HH12_Write(Obj, CTRL_REG4, (data & ~_FS_MASK) | Full_Scale);
}





