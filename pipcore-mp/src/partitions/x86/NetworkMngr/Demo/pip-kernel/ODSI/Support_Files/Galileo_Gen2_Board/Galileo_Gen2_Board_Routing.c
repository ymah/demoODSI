/*
 * Galileo_Gen2_Board.c
 *
 *  Created on: 25 avr. 2018
 *      Author: swhx7055
 */

#include <Galileo_Gen2_Board.h>
#include <Quark_x1000_gen_defs.h>
#include "Expander_Pcal9555_Driver.h"

/*-----------------------------------------------------------------------
 * Static Functions prototypes
 *------------------------------------------------------------------------
 */
static void vGalileoRoute_UART0_to_IO0_and_IO1();
static void vGalileoRoute_GPIO5_to_IO2();
static void vGalileoRoute_GPIO6_to_IO3();
static void vGalileoRoute_GPIO_SUS4_to_IO4();
static void vGalileoRoute_GPIO8_to_IO5();
static void vGalileoRoute_GPIO9_to_IO6();
static void vGalileoRoute_GPIO_SUS2_to_IO9();
static void vGalileoRoute_GPIO2_to_IO10();
static void vGalileoRoute_GPIO_SUS3_to_IO11();
static void vGalileoRoute_GPIO7_to_IO12();
static void vGalileoRoute_GPIO_SUS5_to_IO13();

/*-----------------------------------------------------------------------
 * GPIO pin routing function
 *------------------------------------------------------------------------
 */
void vGalileoRoute_IOs()
{
	vGalileoRoute_UART0_to_IO0_and_IO1();
	vGalileoRoute_GPIO5_to_IO2();
	vGalileoRoute_GPIO6_to_IO3();
	vGalileoRoute_GPIO_SUS4_to_IO4();
	vGalileoRoute_GPIO8_to_IO5();
	vGalileoRoute_GPIO9_to_IO6();

	/*
	 * No routing needed for IO7 and IO8,
	 * because they are directly connected
	 * to the GPIO Expander 1 P0_6 and P1_0
	 * respectively.
	 */

	vGalileoRoute_GPIO_SUS2_to_IO9();
	vGalileoRoute_GPIO2_to_IO10();
	vGalileoRoute_GPIO_SUS3_to_IO11();
	vGalileoRoute_GPIO7_to_IO12();
	vGalileoRoute_GPIO_SUS5_to_IO13();
}

/*-----------------------------------------------------------------------
 * UART0 pins routing
 *------------------------------------------------------------------------
 */
void vGalileoRoute_UART0_to_IO0_and_IO1()
{
	// Route IO0

	// For GpioNums below values 0 to 7 are for Port0 IE. P0-0 - P0-7 and
	// values 8 to 15 are for Port1 IE. P1-0 - P1-7.

	// Disable Pull-ups / pull downs on EXP1 pin for LVL_C_PU0 signal.
	PlatformPcal9555GpioPullup (
	GALILEO_GEN2_IOEXP1_7BIT_SLAVE_ADDR,  // IO Expander 1.
	EXP_PORT0_PIN(1),                                   // P0-1.
	FALSE
	);

	// Make LVL_C_OE0_N an output pin.
	PlatformPcal9555GpioSetDir (
	GALILEO_GEN2_IOEXP1_7BIT_SLAVE_ADDR,  // IO Expander 1.
	EXP_PORT0_PIN(0),                                   // P0-0.
	FALSE);

	// Set level of LVL_C_OE0_N to high.
	PlatformPcal9555GpioSetLevel (GALILEO_GEN2_IOEXP1_7BIT_SLAVE_ADDR, EXP_PORT0_PIN(0), TRUE);

	// Route IO1

	// For GpioNums below values 0 to 7 are for Port0 IE. P0-0 - P0-7 and
	// values 8 to 15 are for Port1 IE. P1-0 - P1-7.

	// Disable Pull-ups / pull downs on EXP0 pin for LVL_B_PU6 signal.
	PlatformPcal9555GpioPullup (
	GALILEO_GEN2_IOEXP0_7BIT_SLAVE_ADDR,  // IO Expander 0.
	EXP_PORT1_PIN(5),                                   // P1-5.
	FALSE
	);

	// Make LVL_B_PU6 an input pin.
	PlatformPcal9555GpioSetDir (
	GALILEO_GEN2_IOEXP0_7BIT_SLAVE_ADDR,  // IO Expander 0.
	EXP_PORT1_PIN(5),                                   // P1-5.
	TRUE
	);

	// Make LVL_B_OE6_N an output pin.
	PlatformPcal9555GpioSetDir (
	GALILEO_GEN2_IOEXP0_7BIT_SLAVE_ADDR,  // IO Expander 0.
	EXP_PORT1_PIN(4),                                   // P1-4.
	FALSE);

	// Set level of LVL_B_OE6_N to low.
	PlatformPcal9555GpioSetLevel (
	GALILEO_GEN2_IOEXP0_7BIT_SLAVE_ADDR,
	EXP_PORT1_PIN(4),
	FALSE);

	// Make MUX7_SEL an output pin.
	PlatformPcal9555GpioSetDir (
	GALILEO_GEN2_IOEXP1_7BIT_SLAVE_ADDR,  // IO Expander 1.
	EXP_PORT1_PIN(5),                                   // P1-5.
	FALSE);

	// Set level of MUX7_SEL to high to route SIU0_TXD (UART0_TXD) to IO1 (Digital 1).
	PlatformPcal9555GpioSetLevel (
	GALILEO_GEN2_IOEXP1_7BIT_SLAVE_ADDR,  // IO Expander 1.
	EXP_PORT1_PIN(5),                                   // P1-5.
	TRUE);
}

static void vGalileoRoute_GPIO5_to_IO2()
{
	// For GpioNums below values 0 to 7 are for Port0 IE. P0-0 - P0-7 and
	// values 8 to 15 are for Port1 IE. P1-0 - P1-7.

	// Disable Pull-ups / pull downs on EXP1 pin for LVL_C_PU1 signal.
	PlatformPcal9555GpioPullup (
	GALILEO_GEN2_IOEXP1_7BIT_SLAVE_ADDR,  				// IO Expander 1.
	EXP_PORT0_PIN(3),                                   // P0-3.
	FALSE
	);
	// external pull-down
	PlatformPcal9555GpioSetDir (
	GALILEO_GEN2_IOEXP1_7BIT_SLAVE_ADDR,  				// IO Expander 1.
	EXP_PORT0_PIN(3),                                   // P0-3.
	FALSE
	);
	// external pull-down
	PlatformPcal9555GpioSetLevel (
	GALILEO_GEN2_IOEXP1_7BIT_SLAVE_ADDR,  				// IO Expander 1.
	EXP_PORT0_PIN(3),                                   // P0-3.
	FALSE
	);

	// Make LVL_C_OE1_N an output pin.
	PlatformPcal9555GpioSetDir (GALILEO_GEN2_IOEXP1_7BIT_SLAVE_ADDR, EXP_PORT0_PIN(2), FALSE); // P0-2.

	// Set level of LVL_C_OE1_N to high.
	PlatformPcal9555GpioSetLevel (GALILEO_GEN2_IOEXP1_7BIT_SLAVE_ADDR, EXP_PORT0_PIN(2), TRUE); // P0-2.
}

static void vGalileoRoute_GPIO6_to_IO3()
{
	// For GpioNums below values 0 to 7 are for Port0 IE. P0-0 - P0-7 and
	// values 8 to 15 are for Port1 IE. P1-0 - P1-7.

	// Disable Pull-ups / pull downs on EXP1 pin for LVL_B_PU0 signal.
	PlatformPcal9555GpioPullup (
	GALILEO_GEN2_IOEXP0_7BIT_SLAVE_ADDR,  				// IO Expander 0.
	EXP_PORT0_PIN(1),                                   // P0-1.
	FALSE
	);
	// external pull-down
	PlatformPcal9555GpioSetDir (
	GALILEO_GEN2_IOEXP0_7BIT_SLAVE_ADDR,  				// IO Expander 0.
	EXP_PORT0_PIN(1),                                   // P0-1.
	FALSE
	);
	// external pull-down
	PlatformPcal9555GpioSetLevel (
	GALILEO_GEN2_IOEXP0_7BIT_SLAVE_ADDR,  				// IO Expander 0.
	EXP_PORT0_PIN(1),                                   // P0-1.
	FALSE
	);

	// Make LVL_B_OE0_N an output pin.
	PlatformPcal9555GpioSetDir (GALILEO_GEN2_IOEXP0_7BIT_SLAVE_ADDR, EXP_PORT0_PIN(0), FALSE); // P0-0.

	// Set level of LVL_B_OE0_N to high.
	PlatformPcal9555GpioSetLevel (GALILEO_GEN2_IOEXP0_7BIT_SLAVE_ADDR, EXP_PORT0_PIN(0), TRUE); // P0-0.
}

static void vGalileoRoute_GPIO_SUS4_to_IO4(void)
{
	// For GpioNums below values 0 to 7 are for Port0 IE. P0-0 - P0-7 and
	// values 8 to 15 are for Port1 IE. P1-0 - P1-7.
	// Disable Pull-ups / pull downs on EXP1 pin for LVL_C_PU2 signal.
	PlatformPcal9555GpioPullup (
	GALILEO_GEN2_IOEXP1_7BIT_SLAVE_ADDR,  // IO Expander 1.
	EXP_PORT0_PIN(5),                                   // P0-5.
	FALSE
	);
	// external pull-down
	PlatformPcal9555GpioSetDir (
	GALILEO_GEN2_IOEXP1_7BIT_SLAVE_ADDR,  // IO Expander 1.
	EXP_PORT0_PIN(5),                                   // P0-5.
	FALSE
	);
	// external pull-down
	PlatformPcal9555GpioSetLevel (
	GALILEO_GEN2_IOEXP1_7BIT_SLAVE_ADDR,  // IO Expander 1.
	EXP_PORT0_PIN(5),                                   // P0-5.
	FALSE
	);

	// Make LVL_C_OE2_N an output pin.
	PlatformPcal9555GpioSetDir (
	GALILEO_GEN2_IOEXP1_7BIT_SLAVE_ADDR,  // IO Expander 1.
	EXP_PORT0_PIN(4),                                   // P0-4.
	FALSE);

	// Set level of LVL_C_OE2_N to high.
	PlatformPcal9555GpioSetLevel (GALILEO_GEN2_IOEXP1_7BIT_SLAVE_ADDR, EXP_PORT0_PIN(4), TRUE); // P0-4.
}

static void vGalileoRoute_GPIO8_to_IO5()
{
	// For GpioNums below values 0 to 7 are for Port0 IE. P0-0 - P0-7 and
	// values 8 to 15 are for Port1 IE. P1-0 - P1-7.

	// Disable Pull-ups / pull downs on EXP1 pin for LVL_B_PU1 signal.
	PlatformPcal9555GpioPullup (
	GALILEO_GEN2_IOEXP0_7BIT_SLAVE_ADDR,  				// IO Expander 0.
	EXP_PORT0_PIN(3),                                   // P0-3.
	FALSE
	);
	// external pull-down
	PlatformPcal9555GpioSetDir (
	GALILEO_GEN2_IOEXP0_7BIT_SLAVE_ADDR,  				// IO Expander 0.
	EXP_PORT0_PIN(3),                                   // P0-3.
	FALSE
	);
	// external pull-down
	PlatformPcal9555GpioSetLevel (
	GALILEO_GEN2_IOEXP0_7BIT_SLAVE_ADDR,  				// IO Expander 0.
	EXP_PORT0_PIN(3),                                   // P0-3.
	FALSE
	);

	// Make LVL_B_OE1_N an output pin.
	PlatformPcal9555GpioSetDir (GALILEO_GEN2_IOEXP0_7BIT_SLAVE_ADDR, EXP_PORT0_PIN(2), FALSE); // P0-2.

	// Set level of LVL_B_OE1_N to high.
	PlatformPcal9555GpioSetLevel (GALILEO_GEN2_IOEXP0_7BIT_SLAVE_ADDR, EXP_PORT0_PIN(2), TRUE); // P0-2.
}

static void vGalileoRoute_GPIO9_to_IO6()
{
	// For GpioNums below values 0 to 7 are for Port0 IE. P0-0 - P0-7 and
	// values 8 to 15 are for Port1 IE. P1-0 - P1-7.

	// Disable Pull-ups / pull downs on EXP1 pin for LVL_B_PU2 signal.
	PlatformPcal9555GpioPullup (
	GALILEO_GEN2_IOEXP0_7BIT_SLAVE_ADDR,  				// IO Expander 0.
	EXP_PORT0_PIN(5),                                   // P0-5.
	FALSE
	);
	// external pull-down
	PlatformPcal9555GpioSetDir (
	GALILEO_GEN2_IOEXP0_7BIT_SLAVE_ADDR,  				// IO Expander 0.
	EXP_PORT0_PIN(5),                                   // P0-5.
	FALSE
	);
	// external pull-down
	PlatformPcal9555GpioSetLevel (
	GALILEO_GEN2_IOEXP0_7BIT_SLAVE_ADDR,  				// IO Expander 0.
	EXP_PORT0_PIN(5),                                   // P0-5.
	FALSE
	);

	// Make LVL_B_OE2_N an output pin.
	PlatformPcal9555GpioSetDir (GALILEO_GEN2_IOEXP0_7BIT_SLAVE_ADDR, EXP_PORT0_PIN(4), FALSE); // P0-4.

	// Set level of LVL_B_OE2_N to high.
	PlatformPcal9555GpioSetLevel (GALILEO_GEN2_IOEXP0_7BIT_SLAVE_ADDR, EXP_PORT0_PIN(4), TRUE); // P0-4.
}

static void vGalileoRoute_GPIO_SUS2_to_IO9()
{
	// For GpioNums below values 0 to 7 are for Port0 IE. P0-0 - P0-7 and
	// values 8 to 15 are for Port1 IE. P1-0 - P1-7.

	// Disable Pull-ups / pull downs on EXP1 pin for LVL_B_PU3 signal.
	PlatformPcal9555GpioPullup (
	GALILEO_GEN2_IOEXP0_7BIT_SLAVE_ADDR,  				// IO Expander 0.
	EXP_PORT0_PIN(7),                                   // P0-7.
	FALSE
	);
	// external pull-down
	PlatformPcal9555GpioSetDir (
	GALILEO_GEN2_IOEXP0_7BIT_SLAVE_ADDR,  				// IO Expander 0.
	EXP_PORT0_PIN(7),                                   // P0-7.
	FALSE
	);
	// external pull-down
	PlatformPcal9555GpioSetLevel (
	GALILEO_GEN2_IOEXP0_7BIT_SLAVE_ADDR,  				// IO Expander 0.
	EXP_PORT0_PIN(7),                                   // P0-7.
	FALSE
	);

	// Make LVL_B_OE3_N an output pin.
	PlatformPcal9555GpioSetDir (GALILEO_GEN2_IOEXP0_7BIT_SLAVE_ADDR, EXP_PORT0_PIN(6), FALSE); // P0-6.

	// Set level of LVL_B_OE3_N to high.
	PlatformPcal9555GpioSetLevel (GALILEO_GEN2_IOEXP0_7BIT_SLAVE_ADDR, EXP_PORT0_PIN(6), TRUE); // P0-6.
}

static void vGalileoRoute_GPIO2_to_IO10(void)
{
	// For GpioNums below values 0 to 7 are for Port0 IE. P0-0 - P0-7 and
	// values 8 to 15 are for Port1 IE. P1-0 - P1-7.

	// Disable Pull-ups / pull downs on EXP0 pin for LVL_B_PU5 signal.
	PlatformPcal9555GpioPullup (
	GALILEO_GEN2_IOEXP0_7BIT_SLAVE_ADDR,  // IO Expander 0.
	EXP_PORT1_PIN(3),                                   // P1-3.
	FALSE
	);
	// external pull-down
	PlatformPcal9555GpioSetDir (
	GALILEO_GEN2_IOEXP0_7BIT_SLAVE_ADDR,  // IO Expander 0.
	EXP_PORT1_PIN(3),                                   // P1-3.
	FALSE
	);
	// external pull-down
	PlatformPcal9555GpioSetLevel (
	GALILEO_GEN2_IOEXP0_7BIT_SLAVE_ADDR,  // IO Expander 0.
	EXP_PORT1_PIN(3),                                   // P1-3.
	FALSE
	);

	// Make LVL_B_OE5_N an output pin.
	PlatformPcal9555GpioSetDir (
	GALILEO_GEN2_IOEXP0_7BIT_SLAVE_ADDR,  // IO Expander 0.
	EXP_PORT1_PIN(2),                                   // P1-2.
	FALSE);

	// Set level of LVL_B_OE5_N to high.
	PlatformPcal9555GpioSetLevel (GALILEO_GEN2_IOEXP0_7BIT_SLAVE_ADDR, EXP_PORT1_PIN(2), TRUE); // P1-2.
}

static void vGalileoRoute_GPIO_SUS3_to_IO11()
{
	// For GpioNums below values 0 to 7 are for Port0 IE. P0-0 - P0-7 and
	// values 8 to 15 are for Port1 IE. P1-0 - P1-7.

	// Disable Pull-ups / pull downs on EXP0 pin for LVL_B_PU4 signal.
	PlatformPcal9555GpioPullup (
	GALILEO_GEN2_IOEXP0_7BIT_SLAVE_ADDR,  // IO Expander 0.
	EXP_PORT1_PIN(1),                                   // P1-1.
	FALSE
	);
	// external pull-down
	PlatformPcal9555GpioSetDir (
	GALILEO_GEN2_IOEXP0_7BIT_SLAVE_ADDR,  // IO Expander 0.
	EXP_PORT1_PIN(1),                                   // P1-1.
	FALSE
	);
	// external pull-down
	PlatformPcal9555GpioSetLevel (
	GALILEO_GEN2_IOEXP0_7BIT_SLAVE_ADDR,  // IO Expander 0.
	EXP_PORT1_PIN(1),                                   // P1-1.
	FALSE
	);

	// Make LVL_B_OE4_N an output pin.
	PlatformPcal9555GpioSetDir (
	GALILEO_GEN2_IOEXP0_7BIT_SLAVE_ADDR,  // IO Expander 0.
	EXP_PORT1_PIN(0),                                   // P1-0.
	FALSE);

	// Set level of LVL_B_OE4_N to high.
	PlatformPcal9555GpioSetLevel (GALILEO_GEN2_IOEXP0_7BIT_SLAVE_ADDR, EXP_PORT1_PIN(0), TRUE); // P1-0.

	// Make MUX5_SEL an output pin.
	PlatformPcal9555GpioSetDir (
	GALILEO_GEN2_IOEXP1_7BIT_SLAVE_ADDR,  // IO Expander 1.
	EXP_PORT1_PIN(4),                                   // P1-4.
	FALSE);

	// Set level of MUX5_SEL to low.
	PlatformPcal9555GpioSetLevel (GALILEO_GEN2_IOEXP1_7BIT_SLAVE_ADDR, EXP_PORT1_PIN(4), FALSE); // P1-4.
}

static void vGalileoRoute_GPIO7_to_IO12()
{
	// For GpioNums below values 0 to 7 are for Port0 IE. P0-0 - P0-7 and
	// values 8 to 15 are for Port1 IE. P1-0 - P1-7.

	// Disable Pull-ups / pull downs on EXP0 pin for LVL_C_PU5 signal.
	PlatformPcal9555GpioPullup (
	GALILEO_GEN2_IOEXP1_7BIT_SLAVE_ADDR,  // IO Expander 1.
	EXP_PORT1_PIN(3),                                   // P1-3.
	FALSE
	);
	// external pull-down
	PlatformPcal9555GpioSetDir (
	GALILEO_GEN2_IOEXP1_7BIT_SLAVE_ADDR,  // IO Expander 1.
	EXP_PORT1_PIN(3),                                   // P1-3.
	FALSE
	);
	// external pull-down
	PlatformPcal9555GpioSetLevel (
	GALILEO_GEN2_IOEXP1_7BIT_SLAVE_ADDR,  // IO Expander 1.
	EXP_PORT1_PIN(3),                                   // P1-3.
	FALSE
	);

	// Make LVL_C_OE5_N an output pin.
	PlatformPcal9555GpioSetDir (
	GALILEO_GEN2_IOEXP1_7BIT_SLAVE_ADDR,  // IO Expander 1.
	EXP_PORT1_PIN(2),                                   // P1-2.
	FALSE);

	// Set level of LVL_C_OE5_N to high.
	PlatformPcal9555GpioSetLevel (GALILEO_GEN2_IOEXP1_7BIT_SLAVE_ADDR, EXP_PORT1_PIN(2), TRUE); // P1-2.
}

static void vGalileoRoute_GPIO_SUS5_to_IO13(void)
{
	 // For GpioNums below values 0 to 7 are for Port0 IE. P0-0 - P0-7 and
	 // values 8 to 15 are for Port1 IE. P1-0 - P1-7.
	 // Disable Pull-ups / pull downs on EXP0 pin for LVL_B_PU7 signal.
	PlatformPcal9555GpioPullup (
	GALILEO_GEN2_IOEXP0_7BIT_SLAVE_ADDR,  // IO Expander 0.
	EXP_PORT1_PIN(7),                                   // P1-7.
    FALSE
    );
	// external pull-down
	PlatformPcal9555GpioSetDir (
	GALILEO_GEN2_IOEXP0_7BIT_SLAVE_ADDR,  // IO Expander 0.
	EXP_PORT1_PIN(7),                                   // P1-7.
    FALSE
    );
	// external pull-down
	PlatformPcal9555GpioSetLevel (
	GALILEO_GEN2_IOEXP0_7BIT_SLAVE_ADDR,  // IO Expander 0.
	EXP_PORT1_PIN(7),                                   // P1-7.
    FALSE
    );


    // Make LVL_B_OE7_N an output pin.
    PlatformPcal9555GpioSetDir (
    GALILEO_GEN2_IOEXP0_7BIT_SLAVE_ADDR,  // IO Expander 0.
	EXP_PORT1_PIN(6),                                   // P1-6.
    FALSE);

    // Set level of LVL_B_OE7_N to high.
    PlatformPcal9555GpioSetLevel (
    GALILEO_GEN2_IOEXP0_7BIT_SLAVE_ADDR,
	EXP_PORT1_PIN(6),
    TRUE);

    // Make MUX8_SEL an output pin.
    PlatformPcal9555GpioSetDir (
    GALILEO_GEN2_IOEXP1_7BIT_SLAVE_ADDR,  // IO Expander 1.
	EXP_PORT1_PIN(6),                                   // P1-6.
    FALSE);

    // Set level of MUX8_SEL to low to route GPIO_SUS<5> to LED.
    PlatformPcal9555GpioSetLevel (
    GALILEO_GEN2_IOEXP1_7BIT_SLAVE_ADDR,  // IO Expander 1.
	EXP_PORT1_PIN(6),                                   // P1-6.
    FALSE);
}

