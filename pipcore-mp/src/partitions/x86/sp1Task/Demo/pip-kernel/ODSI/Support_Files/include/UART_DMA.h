/*
 * UART_DMA.h
 *
 *  Created on: 10 avr. 2018
 *      Author: swhx7055
 */

// UART DMA associated Controller
#define R_DMA_SAR0						0x0		// Channel 0 Source Address
#define B_DMA_SAR0_SAR_RBR				0xFFFFF000 // Current Source Address of DMA transfer as UART controller RBR_THR_DLL register address

#define R_DMA_DAR0						0x8		// Channel 0 Destination Address (must be a memory address because channel 0 is dedicated to the UART controller Received Data)

#define R_DMA_CTL0_L					0x18	// Channel 0 Control LOWER
#define	MASK_DMA_CTL0_L					(1<<0 | 7<<1 | 7<<4 | 3<<7 | 3<<9 | 7<<11 | 7<<14 | 7<<20)
#define B_DMA_CTL0_L_INT_EN				(0<<0)		// Disable interrupts
#define B_DMA_CTL0_L_DST_TR_WIDTH_8		(0<<1)		// Destination transfer width as 32 bits
#define B_DMA_CTL0_L_SRC_TR_WIDTH_8		(0<<4)		// Source transfer width as 8 bits
#define B_DMA_CTL0_L_DINC_INC			(0<<7)		// Destination Address Increment as Increment
#define B_DMA_CTL0_L_SINC_NOCHANGE		(2<<9)	// Source Address Increment as No change
#define B_DMA_CTL0_L_DEST_MSIZE_1		(0<<11)	// Destination Burst Transaction Length as 1 * DST_TR_WIDTH
#define B_DMA_CTL0_L_DEST_MSIZE_8		(2<<11)	// Destination Burst Transaction Length as 8 * DST_TR_WIDTH
#define B_DMA_CTL0_L_SRC_MSIZE_1		(0<<14)	// Source Burst Transaction Length as 1 * SRC_TR_WIDTH
#define B_DMA_CTL0_L_SRC_MSIZE_8		(2<<14)	// Source Burst Transaction Length as 8 * SRC_TR_WIDTH
#define B_DMA_CTL0_L_TT_FC				(2<<20) // Transfer Type as Peripheral to Memory and Flow Control as DMAC

#define R_DMA_CTL0_U					0x1C	// Channel 0 Control UPPER
#define	MASK_DMA_CTL0_U					(4095<<0)
#define B_DMA_CTL0_U_BLOCK_TS			(4095<<0)		// Block length (when the DMAC is the flow controller)

#define R_DMA_CFG0_L					0x40	// Channel 0 Configuration LOWER
#define MASK_DMA_CFG0_L					(7<<5 | 1<<11 | 1<<18 | 1<<19 | 1<<30 | 1<<31)
#define B_DMA_CFG0_L_CH_PRIOR			(1<<5)	// Set channel 0 Priority to 1
#define B_DMA_CFG0_L_HS_SEL_SRC			(0<<11)		// Source Handshake select as Hardware handshake
#define B_DMA_CFG0_L_DST_HS_POL_LOW		(1<<18) // Destination Handshake polarity as Active low
#define B_DMA_CFG0_L_SRC_HS_POL_LOW		(1<<19) // Source Handshake polarity as Active low
#define B_DMA_CFG0_L_RELOAD_SRC			(0<<30) // Reload source enable as disabled
#define B_DMA_CFG0_L_RELOAD_DST			(1<<31) // Reload destination enable as enabled

#define R_DMA_CFG0_U					0x44	// Channel 0 Configuration UPPER
#define MASK_DMA_CFG0_U					(1<<7 | 1<<11)
#define B_DMA_CFG0_U_SRC_PER			(0<<7)		// assigns hardware handshaking interface "0" to the channel source (ignored if CFG0_L.HS_SEL_SRC is set to 1)
#define B_DMA_CFG0_U_DEST_PER			(1<<11)		// assigns hardware handshaking interface "1" to the channel destination (ignored if CFG0_L.HS_SEL_DST is set to 1)

#define R_DMA_CFG_REG					0x398	// DMA Configuration. Used to enable the DMA controller, which must be done before any channel activity can begin.
#define B_DMA_CFG_REG_DMA_EN			BIT0	// DMA global enable

#define R_DMA_CH_EN_REG					0x3A0	// Channel Enable
#define MASK_DMA_CH_EN_REG				(3<<0 | 3<<8)
#define R_DMA_CH_EN_REG_CH_EN			(1<<0)		// Channels Enable register as enable channel 0
#define R_DMA_CH_EN_REG_CH_EN_WE		(1<<8)		// Channels Enable Write Enable as enable channel 0 enable write

void vInitializeGalileo_client_SerialPort_RCVR_DMA();
void client_SerialPort_RCVR_DMA_channel_enable();
void client_SerialPort_RCVR_DMA_enable();
void client_SerialPort_RCVR_DMA_disable();
int vGalileo_UART0_is_data_available();
void vGalileo_UART0_flush_DMA_rcv_buffer();

char uart0_dma_buffer_read_8();
