/*
 * Expander_Pcal9555_Driver.h
 *
 *  Created on: 25 avr. 2018
 *      Author: swhx7055
 */

#ifndef SUPPORT_FILES_INCLUDE_EXPANDER_PCAL9555_DRIVER_H_
#define SUPPORT_FILES_INCLUDE_EXPANDER_PCAL9555_DRIVER_H_

#include "stdint.h"

//---------------------------------------------------------------------
// Three IO Expanders at fixed addresses on Galileo Gen2.
//---------------------------------------------------------------------
#define GALILEO_GEN2_IOEXP0_7BIT_SLAVE_ADDR 0x25
#define GALILEO_GEN2_IOEXP1_7BIT_SLAVE_ADDR 0x26
#define GALILEO_GEN2_IOEXP2_7BIT_SLAVE_ADDR 0x27

//---------------------------------------------------------------------
// PCAL9555 defines
//---------------------------------------------------------------------
#define PCAL9555_REG_OUT_PORT0            0x02
#define PCAL9555_REG_OUT_PORT1            0x03
#define PCAL9555_REG_CFG_PORT0            0x06
#define PCAL9555_REG_CFG_PORT1            0x07
#define PCAL9555_REG_PULL_EN_PORT0        0x46
#define PCAL9555_REG_PULL_EN_PORT1        0x47


#define EXP_PORT0_PIN(n)				(n)
#define EXP_PORT1_PIN(n)				(n+8)

void PlatformPcal9555GpioPullup(uint32_t Pcal9555SlaveAddr, uint32_t GpioNum, uint32_t Enable);
void PlatformPcal9555GpioSetDir(uint32_t Pcal9555SlaveAddr, uint32_t GpioNum, uint32_t CfgAsInput);
void PlatformPcal9555GpioSetLevel(uint32_t Pcal9555SlaveAddr, uint32_t GpioNum, uint32_t HighLevel );

#endif /* SUPPORT_FILES_INCLUDE_EXPANDER_PCAL9555_DRIVER_H_ */

