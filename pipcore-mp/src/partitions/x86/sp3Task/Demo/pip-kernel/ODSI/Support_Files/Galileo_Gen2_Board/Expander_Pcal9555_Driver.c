/*
 * Expander_Pcal9555_Driver.c
 *
 *  Created on: 25 avr. 2018
 *      Author: swhx7055
 */

#include "Expander_Pcal9555_Driver.h"
#include "GPIO_I2C.h"

/*
 * static functions prototypes
 */
static void Pcal9555SetPortRegBit(uint32_t Pcal9555SlaveAddr, uint32_t GpioNum, uint8_t RegBase, uint8_t LogicOne);

/*
 * I2CReadMultipleBytes contains a bug!!!
 * This array contains the PCAL9535A registers stats, so that
 * we don't need to the read a register in order to modifiy
 * some bits without changing the stats of other bits.
 */
struct PCAL9535A_regs
{
	uint8_t output_port_0;
	uint8_t output_port_1;
	uint8_t config_port_0;
	uint8_t config_port_1;
	uint8_t pull_enable_port_0;
	uint8_t pull_enable_port_1;
};

// array for 3 pcal9535a expanders in the galileo gen2 board
static struct PCAL9535A_regs galileo_gen2_pcal9535a_regs[3] =
{
	{
		.output_port_0 = 0xff,
		.output_port_1 = 0xff,
		.config_port_0 = 0xff,
		.config_port_1 = 0xff,
		.pull_enable_port_0 = 0x00,
		.pull_enable_port_1 = 0x00,
	},
	{
		.output_port_0 = 0xff,
		.output_port_1 = 0xff,
		.config_port_0 = 0xff,
		.config_port_1 = 0xff,
		.pull_enable_port_0 = 0x00,
		.pull_enable_port_1 = 0x00,
	},
	{
		.output_port_0 = 0xff,
		.output_port_1 = 0xff,
		.config_port_0 = 0xff,
		.config_port_1 = 0xff,
		.pull_enable_port_0 = 0x00,
		.pull_enable_port_1 = 0x00,
	},
};

void PlatformPcal9555GpioPullup(uint32_t Pcal9555SlaveAddr, uint32_t GpioNum, uint32_t Enable)
{
	Pcal9555SetPortRegBit(Pcal9555SlaveAddr, GpioNum, PCAL9555_REG_PULL_EN_PORT0, Enable );
}
/*-----------------------------------------------------------*/

void PlatformPcal9555GpioSetDir(uint32_t Pcal9555SlaveAddr, uint32_t GpioNum, uint32_t CfgAsInput)
{
	Pcal9555SetPortRegBit(Pcal9555SlaveAddr, GpioNum, PCAL9555_REG_CFG_PORT0, CfgAsInput);
}
/*-----------------------------------------------------------*/

void PlatformPcal9555GpioSetLevel(uint32_t Pcal9555SlaveAddr, uint32_t GpioNum, uint32_t HighLevel )
{
	Pcal9555SetPortRegBit(Pcal9555SlaveAddr, GpioNum, PCAL9555_REG_OUT_PORT0, HighLevel );
}

/*-----------------------------------------------------------------------
  * Pcal9555 chips used on Galileo Gen 2 boards (see FAB-H schematic)
  *------------------------------------------------------------------------
  */
static void Pcal9555SetPortRegBit(uint32_t Pcal9555SlaveAddr, uint32_t GpioNum, uint8_t RegBase, uint8_t LogicOne)
{
	//uintn_t            ReadLength;
	uintn_t            WriteLength;
	uint8_t            Data[2];
	uint8_t            *RegValuePtr;
	uint8_t            GpioNumMask;
	uint8_t            SubAddr;
	I2C_DEVICE_ADDRESS I2cDeviceAddr;
	I2C_ADDR_MODE      I2cAddrMode;

	// Set I2C address and mode.
	I2cDeviceAddr.I2CDeviceAddress = (uintn_t) Pcal9555SlaveAddr;
	I2cAddrMode = EfiI2CSevenBitAddrMode;

	// Set I2C subaddress and GPIO mask.
	if (GpioNum < 8)
	{
	 SubAddr = RegBase;
	 GpioNumMask = (uintn_t) (1 << GpioNum);
	}
	else
	{
	 SubAddr = RegBase + 1;
	 GpioNumMask = (uintn_t) (1 << (GpioNum - 8));
	}

	// Output port value always at 2nd byte in Data variable.
	RegValuePtr = &Data[1];

	// On read entry - sub address at 2nd byte, on read exit - output
	// port value in 2nd byte.
	Data[1] = SubAddr;
	WriteLength = 1;
	//ReadLength = 1;

	/*
	* Their is a bug in I2CReadMultipleBytes => replaced by struct PCAL9593_regs
	* in order to keep trace of pcal9593 registers values
	*/
	// I2CReadMultipleBytes(I2cDeviceAddr, I2cAddrMode, &WriteLength, &ReadLength,  &Data[1])

	struct PCAL9535A_regs *pcal9535a_regs;
	pcal9535a_regs = &galileo_gen2_pcal9535a_regs[Pcal9555SlaveAddr - GALILEO_GEN2_IOEXP0_7BIT_SLAVE_ADDR];

	switch(SubAddr)
	{
	case PCAL9555_REG_OUT_PORT0:
	 Data[1] = pcal9535a_regs->output_port_0;
	 break;
	case PCAL9555_REG_OUT_PORT1:
	 Data[1] = pcal9535a_regs->output_port_1;
	 break;
	case PCAL9555_REG_CFG_PORT0:
	 Data[1] = pcal9535a_regs->config_port_0;
	 break;
	case PCAL9555_REG_CFG_PORT1:
	 Data[1] = pcal9535a_regs->config_port_1;
	 break;
	case PCAL9555_REG_PULL_EN_PORT0:
	 Data[1] = pcal9535a_regs->pull_enable_port_0;
	 break;
	case PCAL9555_REG_PULL_EN_PORT1:
	 Data[1] = pcal9535a_regs->pull_enable_port_1;
	 break;
	}

	// Adjust output port bit using mask value.
	if (LogicOne)
	 *RegValuePtr = *RegValuePtr | GpioNumMask;
	else
	 *RegValuePtr = *RegValuePtr & ~(GpioNumMask);

	switch(SubAddr)
	{
	case PCAL9555_REG_OUT_PORT0:
	 pcal9535a_regs->output_port_0 = Data[1];
	 break;
	case PCAL9555_REG_OUT_PORT1:
	 pcal9535a_regs->output_port_1 = Data[1];
	 break;
	case PCAL9555_REG_CFG_PORT0:
	 pcal9535a_regs->config_port_0 = Data[1];
	 break;
	case PCAL9555_REG_CFG_PORT1:
	 pcal9535a_regs->config_port_1 = Data[1];
	 break;
	case PCAL9555_REG_PULL_EN_PORT0:
	 pcal9535a_regs->pull_enable_port_0 = Data[1];
	 break;
	case PCAL9555_REG_PULL_EN_PORT1:
	 pcal9535a_regs->pull_enable_port_1 = Data[1];
	 break;
	}

	// Update register. Sub address at 1st byte, value at 2nd byte.
	WriteLength = 2;
	Data[0] = SubAddr;
	I2CWriteMultipleBytes(I2cDeviceAddr,I2cAddrMode, &WriteLength, Data);
}

