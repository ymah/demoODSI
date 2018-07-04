/*
 * UART_DMA.c
 *
 *  Created on: 10 avr. 2018
 *      Author: swhx7055
 */


#include <Quark_x1000_support.h>
#include "UART_DMA.h"
#include "task.h"
#include "string.h"

#define BUFFER_SIZE		4095

static uint8_t *dma_buffer;
static uint8_t *vDma_buffer;

static uint32_t bGalileo_UART0_DMAC_Initialized = FALSE;
//static uint32_t bGalileo_UART1_DMAC_Initialized = FALSE;

static uint32_t DMA_UART_0_MMIO_Base = 0UL;
static uint32_t DMA_UART_1_MMIO_Base = 0UL;

static void vInitializeGalileoUART_RCVR_DMA(uint32_t portnumber);

static uint32_t buffer_index = 0;

void set_dma_buffer(uint32_t dma_buffer_addr)
{
	dma_buffer = dma_buffer_addr;
}

void set_v_dma_buffer(uint32_t v_dma_buffer_addr)
{
	vDma_buffer = v_dma_buffer_addr;
}

/*
 * Use DMA
 * returns 1 if their is data available to be read
 */
int vGalileo_UART0_is_data_available()
{
	volatile uint32_t dest_addr = 0;
	int ret = 0;

	dest_addr = mem_read(DMA_UART_0_MMIO_Base, R_DMA_DAR0, 4);
	printf("Dest_addr\t\t\t\t\t%x\r\n", dest_addr);
	printf("DMA_buffer\t\t\t\t\t%x\r\n", dma_buffer);
	printf("Buffer_index\t\t\t\t\t%x\r\n", buffer_index);
	// checks if the dest_addr changed
	if((dest_addr - (uint32_t)dma_buffer) != buffer_index)
	{
		ret = 1;
	}

	return ret;
}

/*
 * ignore all incoming buffered messages
 */
void vGalileo_UART0_flush_DMA_rcv_buffer()
{
	volatile uint32_t dest_addr = 0;

	dest_addr = mem_read(DMA_UART_0_MMIO_Base, R_DMA_DAR0, 4);

	// checks if the dest_addr changed
	if((dest_addr - (uint32_t)dma_buffer) != buffer_index)
	{
		buffer_index = dest_addr - (uint32_t)dma_buffer;
	}
}

char uart0_dma_buffer_read_8()
{
	volatile uint32_t dest_addr = 0;
	char data_8 = 0;

	/* Block for 1ms. */
	const TickType_t xDelay = 100;

	dest_addr = mem_read(DMA_UART_0_MMIO_Base, R_DMA_DAR0, 4);

	// checks if the dest_addr changed
	while((dest_addr - (uint32_t)dma_buffer) == buffer_index)
	{
		dest_addr = mem_read(DMA_UART_0_MMIO_Base, R_DMA_DAR0, 4);
	}

	// there is something to read
	vTaskDelay_ms( xDelay );
	data_8 = vDma_buffer[buffer_index];
	buffer_index++;
	if(buffer_index >= BUFFER_SIZE)
	{
		buffer_index = 0;
	}

	printf("%x\t%c\r\n", data_8, data_8);

	return data_8;
}
/*
char uart0_dma_buffer_read_8()
{
	char data_8 = 0;

	data_8 = dma_buffer[buffer_index];
	while(data_8 == 0)
	{
		data_8 = dma_buffer[buffer_index];
	}

	dma_buffer[buffer_index] = 0;
	buffer_index++;
	if(buffer_index >= BUFFER_SIZE)
	{
		buffer_index = 0;
	}

	return data_8;
}
*/


void vInitializeGalileo_client_SerialPort_RCVR_DMA()
{
 	if( bGalileo_UART0_DMAC_Initialized == FALSE )
	{
		/* Initialise for 115200, 8, 1, none and no handshaking */
 		vInitializeGalileoUART_RCVR_DMA(CLIENT_SERIAL_PORT);
 		bGalileo_UART0_DMAC_Initialized = TRUE;
	}
}

void client_SerialPort_RCVR_DMA_channel_enable()
{
	volatile uint32_t input_data = 0;
	input_data = mem_read(DMA_UART_0_MMIO_Base, R_DMA_CH_EN_REG, 4);
	input_data &= ~MASK_DMA_CH_EN_REG;
	input_data |= R_DMA_CH_EN_REG_CH_EN;
	mem_write(DMA_UART_0_MMIO_Base, R_DMA_CH_EN_REG, 4, input_data);
}

void client_SerialPort_RCVR_DMA_enable()
{
	 mem_write(DMA_UART_0_MMIO_Base, R_DMA_CFG_REG, 1, (uint8_t)(B_DMA_CFG_REG_DMA_EN));
}

void client_SerialPort_RCVR_DMA_disable()
{
	 mem_write(DMA_UART_0_MMIO_Base, R_DMA_CFG_REG, 1, (uint8_t)(~B_DMA_CFG_REG_DMA_EN));
}

static void vInitializeGalileoUART_RCVR_DMA(uint32_t portnumber)
 {
	uint32_t bar1;
	uint32_t UART_0_PCI_Base = 0UL;
	uint32_t UART_1_PCI_Base = 0UL;
	volatile uint32_t input_data = 0;

	if (portnumber == DEBUG_SERIAL_PORT)
	{
		UART_1_PCI_Base = MMIO_PCI_ADDRESS(0, 20, 5, 0);
		bar1 = mem_read(UART_1_PCI_Base, 0x14, 4);
		DMA_UART_1_MMIO_Base = bar1;
	}
	else
	{
		UART_0_PCI_Base = MMIO_PCI_ADDRESS(0, 20, 1, 0);
		bar1 = mem_read(UART_0_PCI_Base, 0x14, 4);
		DMA_UART_0_MMIO_Base = bar1;
	}

 }
