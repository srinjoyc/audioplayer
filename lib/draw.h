/*
 * draw.h
 *
 *  Created on: 2017-02-09
 *      Author: z2x9a
 */

#ifndef DRAW_H_
#define DRAW_H_

#define DrawHLine		0x1
#define DrawVLine		0x2
#define DrawLine		0x3
#define PutAPixel		0xA
#define GetAPixel		0xB
#define ProgramPaletteColour   	0x10

#define WAIT_FOR_GRAPHICS		while((GraphicsStatusReg & 0x0001) != 0x0001);

#define GraphicsCommandReg   			(*(volatile unsigned short int *)(0x84000000))
#define GraphicsStatusReg   			(*(volatile unsigned short int *)(0x84000000))
#define GraphicsX1Reg   				(*(volatile unsigned short int *)(0x84000002))
#define GraphicsY1Reg	   				(*(volatile unsigned short int *)(0x84000004))
#define GraphicsX2Reg	   				(*(volatile unsigned short int *)(0x84000006))
#define GraphicsY2Reg					(*(volatile unsigned short int *)(0x84000008))
#define GraphicsColourReg				(*(volatile unsigned short int *)(0x8400000E))
#define GraphicsBackGroundColourReg   	(*(volatile unsigned short int *)(0x84000010))



#endif /* DRAW_H_ */
