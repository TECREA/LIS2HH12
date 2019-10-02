/*
 * LIS2HH12.h
 *
 *  Created on: 13/09/2019
 *      Author: manuelposada
 */

#ifndef DRIVERS_HD_LIS2HH12_H_
#define DRIVERS_HD_LIS2HH12_H_

#include <stdint.h>

#define LIS2HH12_ON       0x01U
#define LIS2HH12_OFF      0x00U

/*
 **  =====================================================================================
 **  || Command || SAD[6:2] || SAD[1] = !SA0 || SAD[0] = SA0 || R/W || SAD+R/W  || HEX  ||
 **  ====================================================================================
 **  ||   Read  ||  00111   ||      1        ||      0       ||  1  || 00111101 ||  3D  ||
 **  ||   Write ||  00111   ||      1        ||      0       ||  0  || 00111100 ||  3C  ||
 **  ||   Read  ||  00111   ||      0        ||      1       ||  1  || 00111011 ||  3B  ||
 **  ||   Write ||  00111   ||      0        ||      1       ||  0  || 00111010 ||  3A  ||
 **  =====================================================================================
*/
#define __VCC__   0x01U
#define __GND__   0x00U
#define __SA0__   __VCC__

#if __SA0__ == __VCC__
	#define ADDRESS   0x3AU
#elif __SA0__ == __GND__
	#define ADDRESS   0x3CU
#endif

/*
 ** ===================================================================
 **  Main Registers
 **
 ** ===================================================================
*/
#define TEMP_L      0x0BU
#define TEMP_H      0x0CU
#define WHO_AM_I    0x0FU
/*
 ** ===================================================================
 **	 Control Register 1 (R/W)
 ** ===================================================================
*/
#define CTRL_REG1   0x20U			      // Register Number CTRL1
#define XEN        (0x01U << 0U)          // Enable X-axis
#define YEN		   (0x01U << 1U)     	  // Enable Y-axis
#define ZEN		   (0x01U << 2U)          // Enable Z-axis
#define BDU        (0x01U << 3U)          // Block Data Update
#define HR         (0x01U << 7U)          // High resolution bit
#define XYZEN      ((XEN)|(YEN)|(ZEN))    // Enable All-axis XYZ

/*
 **    =========================================
 **    || ODR2 || ODR1 || ODR0 || POWER-DOWN ||
 **    =========================================
 **    ||   0  ||  0   ||  0  || Power-Down  ||
 **    ||   0  ||  0   ||  1  ||   10Hz      ||
 **    ||   0  ||  1   ||  0  ||   50Hz      ||
 **    ||   0  ||  1   ||  1  ||   100Hz     ||
 **    ||   1  ||  0   ||  0  ||   200Hz     ||
 **    ||   1  ||  0   ||  1  ||   400Hz     ||
 **    ||   1  ||  1   ||  0  ||   800Hz     ||
 **    =========================================
*/
#define _ODR_MASK       (0x07U << 4U)       // Mask to clear bits
#define ODR_POWER_DOWN  (0x00U << 4U)		// Power-Down
#define ODR_10HZ        (0x01U << 4U)       // 10Hz
#define ODR_50HZ        (0x02U << 4U)       // 50Hz
#define ODR_100HZ       (0x03U << 4U)   	// 100Hz
#define ODR_200HZ       (0x04U << 4U)		// 200Hz
#define ODR_400HZ       (0x05U << 4U)       // 400Hz
#define ODR_800HZ       (0x06U << 4U)       // 800Hz

/*
 ** ===================================================================
 **	 Control Register 2 (R/W)
 ** ===================================================================
*/
#define CTRL2		0x21U
/*
 ** ===================================================================
 **	 Control Register 4 (R/W)
 ** ===================================================================
*/
#define CTRL_REG4   0x23U

#define SIM              ()
#define I2C_DISABLE      ()
#define IF_ADD_INC       ()
#define BW_SCALE_ODR     ()

#define _FS_MASK          (0x03U << 4U)
#define _FS_2G_           (0x00U << 4U)
#define _FS_4G_           (0x01U << 4U)
#define _FS_8G_           (0x03U << 4U)

/*
 ** ===================================================================
 **	 Control Register 2 (R/W)
 ** ===================================================================
*/
#define STATUS       0x27U
#define OUT_X_L      0x28U
#define OUT_X_H      0x29U
#define OUT_Y_L      0x2AU
#define OUT_Y_H      0x2BU
#define OUT_Z_L      0x2CU
#define OUT_Z_H      0x2DU

/*
 ** ===================================================================
 **	 Type
 ** ===================================================================
*/
typedef void (*Write_Fcn )(uint8_t, void*, uint8_t);
typedef void (*Read_Fcn  )(uint8_t, void*, uint8_t);

typedef struct {
	Write_Fcn Write;
	Read_Fcn  Read;
	uint8_t   Address;
}LIS2HH12_t;

/*
 ** ===================================================================
 **	Headers functions
 ** ===================================================================
*/

uint8_t LIS2HH12_Read(LIS2HH12_t *Obj, uint8_t Reg );
uint8_t LIS2HH12_Who_Am_I(LIS2HH12_t *Obj);
void LIS2HH12_Init(LIS2HH12_t *Obj, Write_Fcn Write, Read_Fcn Read, uint8_t Addres_Device);
void LIS2HH12_Write(LIS2HH12_t *Obj, uint8_t Reg, uint8_t data);
void LIS2HH12_PowerDown_Mode(LIS2HH12_t *Obj);
void LIS2HH12_Active_Mode(LIS2HH12_t *Obj, uint8_t Frecuency);
void LIS2HH12_ReadXYZ(LIS2HH12_t *Obj, int16_t *Data);
void LIS2HH12_Update_BDU(LIS2HH12_t *Obj, uint8_t BDU_ON_OFF);
void LIS2HH12_Full_Scale(LIS2HH12_t *Obj, uint8_t Full_Scale);

#endif /* DRIVERS_HD_LIS2HH12_H_ */
