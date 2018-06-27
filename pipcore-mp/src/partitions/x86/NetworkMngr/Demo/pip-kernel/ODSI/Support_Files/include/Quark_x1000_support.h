/*--------------------------------------------------------------------
 Copyright(c) 2015 Intel Corporation. All rights reserved.

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions
 are met:

 * Redistributions of source code must retain the above copyright
 notice, this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright
 notice, this list of conditions and the following disclaimer in
 the documentation and/or other materials provided with the
 distribution.
 * Neither the name of Intel Corporation nor the names of its
 contributors may be used to endorse or promote products derived
 from this software without specific prior written permission.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 --------------------------------------------------------------------*/

#ifndef __GALILEO_SUPPORT_H__
#define __GALILEO_SUPPORT_H__

#ifdef __cplusplus
	extern "C" {
#endif

//---------------------------------------------------------------------
// Any required includes
//---------------------------------------------------------------------
#include "FreeRTOS.h"
#include "semphr.h"
#include <Quark_x1000_gen_defs.h>
#include "GPIO_I2C.h"

//---------------------------------------------------------------------
// Application main entry point
//---------------------------------------------------------------------
extern void main( void );

//---------------------------------------------------------------------
// Defines for GDT
//---------------------------------------------------------------------
#define	NGDE				8		/* Number of global descriptor entries	*/
#define FLAGS_GRANULARITY	0x80
#define FLAGS_SIZE			0x40
#define	FLAGS_SETTINGS		( FLAGS_GRANULARITY | FLAGS_SIZE )
#define	PAGE_SIZE			4096

struct __attribute__ ((__packed__)) sd
{
	unsigned short	sd_lolimit;
	unsigned short	sd_lobase;
	unsigned char	sd_midbase;
	unsigned char   sd_access;
	unsigned char	sd_hilim_fl;
	unsigned char	sd_hibase;
};

void setsegs();

//---------------------------------------------------------------------
// Debug serial port display update definitions
//---------------------------------------------------------------------
#define ANSI_CLEAR_SB			"\e[3J"
#define ANSI_CLEAR_LINE			"\x1b[2K"
#define ANSI_CLEAR_SCREEN		"\x1b[2J"
#define ANSI_COLOR_RED     		"\x1b[31m"
#define ANSI_COLOR_GREEN   		"\x1b[32m"
#define ANSI_COLOR_YELLOW  		"\x1b[33m"
#define ANSI_COLOR_BLUE    		"\x1b[34m"
#define ANSI_COLOR_MAGENTA 		"\x1b[35m"
#define ANSI_COLOR_CYAN    		"\x1b[36m"
#define ANSI_COLOR_RESET   		"\x1b[0m"
#define ANSI_COLOR_WHITE   		ANSI_COLOR_RESET

#define DEFAULT_SCREEN_COLOR	ANSI_COLOR_YELLOW
#define DEFAULT_BANNER_COLOR	ANSI_COLOR_CYAN

#define ANSI_HIDE_CURSOR		"\x1b[?25l"
#define ANSI_SHOW_CURSOR		"\x1b[?25h"

void ClearScreen(void);
void MoveToScreenPosition(uint8_t row, uint8_t col);
void UngatedMoveToScreenPosition(uint8_t row, uint8_t col);
void SetScreenColor(const char *);
void g_printf(const char *format, ...);
void g_printf_rcc(uint8_t row, uint8_t col, const char *color, const char *format, ...);
void vPrintBanner( void );

//---------------------------------------------------------------------
// 8259 PIC (programmable interrupt controller) definitions
//---------------------------------------------------------------------
#define IMR1 (0x21)       /* Interrupt Mask Register #1           */
#define IMR2 (0xA1)       /* Interrupt Mask Register #2           */
#define ICU1 (0x20)
#define ICU2 (0xA0)
#define EOI  (0x20)

void vInitialize8259Chips(void);
void vClearIRQMask(uint8_t IRQNumber);
void vSetIRQMask(uint8_t IRQNumber);

//---------------------------------------------------------------------
// 82C54 PIT (programmable interval timer) definitions
//---------------------------------------------------------------------
#define GATE_CONTROL	0x61
#define CHANNEL2_DATA	0x42
#define	MODE_REGISTER	0x43
#define ONESHOT_MODE	0xB2
#define	CLKBASE			0x40
#define	CLKCNTL			MODE_REGISTER

void vInitializePIT(void);

//---------------------------------------------------------------------
// LED support for main_blinky()
//---------------------------------------------------------------------
#define LED_ON			( 1 )
#define LED_OFF	  		( 0 )

uint32_t ulBlinkLED(void); /* Blink the LED and return the LED status. */

//---------------------------------------------------------------------
// Serial port and his associated DMA Controller support definitions
//---------------------------------------------------------------------
#define CLIENT_SERIAL_PORT 				0
#define DEBUG_SERIAL_PORT 				1

#define R_UART_RBR_THR_DLL              0 		// Receive Buffer Register(RBR), reading this register when the DLAB bit (LCR[7]) is zero; Transmit Holding Register (THR), writing to this register when the DLAB is zero; Divisor Latch Low (DLL), when DLAB bit is one
#define R_UART_IER                      0x04
#define R_UART_BAUD_THR                 R_UART_RBR_THR_DLL
#define R_UART_BAUD_LOW                 R_UART_BAUD_THR
#define R_UART_BAUD_HIGH                R_UART_IER
#define R_UART_IIR_FCR                  0x08 // Interrupt Identification Register (IIR) if reading; FIFO Control Register (FCR) if writing.
#define B_UART_FCR_FIFOE              	BIT0 // FIFO Enable, enables/ disables the transmit (XMIT) and receive (RCVR) FIFO's. Whenever the value of this bit is changed both the XMIT and RCVR controller portion of FIFO's will be reset.
#define B_UART_FCR_RFIFOR				BIT1 // RCVR FIFO Reset, resets the control portion of the receive FIFO and treats the FIFO as empty. This will also de-assert the DMA RX request and single signals.  NOTE that this bit is 'self-clearing' and it is not necessary to clear this bit.
#define B_UART_FCR_XFIFOR				BIT2 // XMIT FIFO Reset, resets the control portion of the transmit FIFO and treats the FIFO as empty. This will also de-assert the DMA TX request and single signals. NOTE that this bit is 'self-clearing' and it is not necessary to clear this bit.
#define B_UART_FCR_DMAM					BIT3 // not used
#define B_UART_FCR_TET_HALF_FULL		0x30 // TX EMPTY Trigger as FIFO 1/2 Full (It also determines when the DMA support is requested if the DMA is enabled)
#define B_UART_FCR_RT_ONE_CHAR			0x00 // RCVR Trigger as 1 character in the FIFO (It also determines when the DMA support is requested if the DMA is enabled)
#define B_UART_FCR_RT_HALF_FULL			0x80 // RCVR Trigger as FIFO 1/2 FULL (It also determines when the DMA support is requested if the DMA is enabled)
#define R_UART_LCR                      0x0C
#define B_UART_LCR_DLAB                 BIT7 // must be cleared after initial baud rate setup in order to access other registers.
#define R_UART_MCR                      0x10
#define R_UART_LSR                      0x14
#define B_UART_LSR_RXRDY                BIT0
#define B_UART_LSR_OE                   BIT1
#define B_UART_LSR_PE                   BIT2
#define B_UART_LSR_FE                   BIT3
#define B_UART_LSR_BI                   BIT4
#define B_UART_LSR_TXRDY                BIT5
#define B_UART_LSR_TEMT                 BIT6
#define R_UART_MSR                      0x18
#define R_UART_SCR                      0x1C // is for programmers to use as a temporary storage space. It has no defined purpose in the UART.

///////////////////////////////////////////////////

void vInitializeGalileo_debug_SerialPort();
void vInitializeGalileo_client_SerialPort();

void vGalileoPrintc(char c);
uint8_t ucGalileoGetchar();
void vGalileoPuts(const char *string);

unsigned long vGalileo_UART0_read(char *buf, unsigned long size);
unsigned long vGalileo_UART0_read_line(char *buf, unsigned long max_size);
void vGalileo_UART0_write(const char *buf, unsigned long size);
void vGalileo_UART0_put_char(char c);
uint8_t vGalileo_UART0_get_char();

#ifdef __cplusplus
	} /* extern C */
#endif

#endif /* __GALILEO_SUPPORT_H__ */

