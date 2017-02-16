/*
 * GraphicsDriver.h
 *
 *  Created on: 2017-02-09
 *      Author: z2x9a
 */

#ifndef GRAPHICSDRIVER_H_
#define GRAPHICSDRIVER_H_

#include <stdio.h>
#include "Colours.h"
#include "draw.h"

#define XRES 800
#define YRES 480

#define FONT2_XPIXELS	10				// width of Font2 characters in pixels (no spacing)
#define FONT2_YPIXELS	14



//	Other Constants

#define TRUE 1
#define FALSE 0

void DrawHorizontalLineHardware(int Xstart, int Xstop, int y, int colour);
void DrawHorizontalLine(int Xstart, int Xstop, int y, int colour);
void DrawVerticalLine(int x, int Ystart, int Ystop, int colour);
void DrawRectangle(int Xstart, int Ystart, int Xstop, int Ystop, int colour, int ShouldFill);
void DrawBorderedRectangle(int Xstart, int Ystart, int Xstop, int Ystop, int BorderWidth, int BorderColour, int FillColour, int ShouldFill);
void Line(int x1, int y1, int x2, int y2, int Colour);
void Circle(int Xin, int Yin, int rad, int Colour, int ShouldFill);
void SkinnyRoundedEdges(int Xin, int Yin, int rad, int Colour, int WhichCorner);
void FilledRoundedEdges(int Xin, int Yin, int rad, int Colour, int WhichCorner);
void DrawBorderedRoundedRectangle(int Xstart, int Ystart, int Xstop, int Ystop, int BorderWidth, int Radius, int BorderColour, int FillColour);
void DrawRoundedRectangle(int Xstart, int Ystart, int Xstop, int Ystop, int Radius, int Colour, int ShouldFill);
void OutGraphicsCharFont2(int x, int y, int colour, int backgroundcolour, int c, int Erase);
void OutGraphicsCharFont1(int x, int y, int fontcolour, int backgroundcolour, int c, int Erase);
void ClearScreen();






extern const unsigned char Font5x7[][7] ;
extern const unsigned short int Font10x14[][14] ;



#endif /* GRAPHICSDRIVER_H_ */
