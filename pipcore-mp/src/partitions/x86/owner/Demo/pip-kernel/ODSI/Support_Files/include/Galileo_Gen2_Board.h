/*
 * Galileo_Gen2_Board.h
 *
 *  Created on: 25 avr. 2018
 *      Author: swhx7055
 */

#include "stdint.h"

#ifndef SUPPORT_FILES_GALILEO_GEN2_BOARD_INCLUDE_GALILEO_GEN2_BOARD_H_
#define SUPPORT_FILES_GALILEO_GEN2_BOARD_INCLUDE_GALILEO_GEN2_BOARD_H_

#define GALILEO_GEN2_IO_0		0
#define GALILEO_GEN2_IO_1		1
#define GALILEO_GEN2_IO_2		2
#define GALILEO_GEN2_IO_3		3
#define GALILEO_GEN2_IO_4		4
#define GALILEO_GEN2_IO_5		5
#define GALILEO_GEN2_IO_6		6
#define GALILEO_GEN2_IO_7		7
#define GALILEO_GEN2_IO_8		8
#define GALILEO_GEN2_IO_9		9
#define GALILEO_GEN2_IO_10		10
#define GALILEO_GEN2_IO_11		11
#define GALILEO_GEN2_IO_12		12
#define GALILEO_GEN2_IO_13		13

void vGalileoRoute_IOs();

void Galileo_Gen2_Init_IO7_and_IO8();

void Galileo_Gen2_Set_IO_Direction(uint32_t Galileo_Board_IO_Number, uint32_t Direction);
void Galileo_Gen2_Set_IO_Level(uint32_t Galileo_Board_IO_Number, uint32_t Level);

/*
 * Test IOs
 */
void Test_Galileo_Gen2_Blink_IOs();

#endif /* SUPPORT_FILES_GALILEO_GEN2_BOARD_INCLUDE_GALILEO_GEN2_BOARD_H_ */
