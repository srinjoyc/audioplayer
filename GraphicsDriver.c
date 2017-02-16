/*
 * "Hello World" example.
 *
 * This example prints 'Hello from Nios II' to the STDOUT stream. It runs on
 * the Nios II 'standard', 'full_featured', 'fast', and 'low_cost' example
 * designs. It runs with or without the MicroC/OS-II RTOS and requires a STDOUT
 * device in your system's hardware.
 * The memory footprint of this hosted application is ~69 kbytes by default
 * using the standard reference design.
 *
 * For a reduced footprint version of this template, and an explanation of how
 * to reduce the memory footprint for a given application, see the
 * "small_hello_world" template.
 *
 */

#include "lib/GraphicsDriver.h"


void DrawHorizontalLineHardware(int Xstart, int Xstop, int y, int colour)
{
	if(Xstart > Xstop){
		int temp = Xstart;
		Xstart = Xstop;
		Xstop = temp;
	}
	WAIT_FOR_GRAPHICS;
	GraphicsX1Reg = Xstart;			// write coords to x1, y1
	GraphicsY1Reg = y;
	GraphicsX2Reg = Xstop;
	GraphicsColourReg = colour;		// set pixel colour with a palette number
	GraphicsCommandReg = DrawHLine;


}

void DrawHorizontalLine(int Xstart, int Xstop, int y, int colour)
{
	if(Xstart > Xstop){
		int temp = Xstart;
		Xstart = Xstop;
		Xstop = temp;
	}
	int i;
	for(i = Xstart; i <= Xstop; i++){
		WriteAPixel(i, y , colour);
	}
}

void DrawVerticalLine(int x, int Ystart, int Ystop, int colour)
{
	if(Ystart > Ystop){
		int temp = Ystart;
		Ystart = Ystop;
		Ystop = temp;
	}
	int i;
	for( i = Ystart; i <= Ystop; i++){
		WriteAPixel(x, i , colour);
	}

}

void DrawRectangle(int Xstart, int Ystart, int Xstop, int Ystop, int colour, int ShouldFill)
{
	if(Ystart > Ystop){
		int temp = Ystart;
		Ystart = Ystop;
		Ystop = temp;
	}
	if(Xstart > Xstop){
		int temp = Xstart;
		Xstart = Xstop;
		Xstop = temp;
	}
	if(ShouldFill != 0){
		int j;
		for( j = Ystart; j <= Ystop; j++){
			DrawHorizontalLine(Xstart, Xstop, j, colour);
		}
	}else{
		DrawVerticalLine(Xstart,Ystart-1,Ystop-1, colour);// left side
		DrawVerticalLine(Xstop,Ystart-1,Ystop-1, colour);//right side
		DrawHorizontalLine(Xstart,Xstop,Ystart, colour); //Top
		DrawHorizontalLine(Xstart,Xstop,Ystop, colour);	//Bottom
	}
}

void DrawBorderedRectangle(int Xstart, int Ystart, int Xstop, int Ystop, int BorderWidth, int BorderColour, int FillColour, int ShouldFill)
{
	if(Ystart > Ystop){
		int temp = Ystart;
		Ystart = Ystop;
		Ystop = temp;
	}
	if(Xstart > Xstop){
		int temp = Xstart;
		Xstart = Xstop;
		Xstop = temp;
	}
	if(ShouldFill != 0){
		DrawRectangle(Xstart+BorderWidth, Ystart+BorderWidth, Xstop-BorderWidth, Ystop-BorderWidth,FillColour,ShouldFill);
	}
	int i;
	for(i = 0; i <= BorderWidth; i++ ){
		DrawVerticalLine(Xstart+i,Ystart,Ystop, BorderColour);// left side
		DrawVerticalLine(Xstop-i,Ystart,Ystop, BorderColour);// left side
		DrawHorizontalLine(Xstart,Xstop,Ystart+i, BorderColour); //Top
		DrawHorizontalLine(Xstart,Xstop,Ystop-i, BorderColour);	//Bottom
	}
}
void ClearScreen(){
	DrawRectangle(0,0,XRES,YRES,WHITE, 1);
}


int abs(int a)
{
    if(a < 0)
        return -a ;
    else
        return a ;
}

int sign(int a)
{
    if(a < 0)
        return -1 ;
    else if (a == 0)
        return 0 ;
    else
        return 1 ;
}


void Line(int x1, int y1, int x2, int y2, int Colour){
    int x = x1;
    int y = y1;
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);

    int s1 = sign(x2 - x1);
    int s2 = sign(y2 - y1);
    int i, temp, interchange = 0, error ;

// if x1=x2 and y1=y2 then it is a line of zero length

    if(dx == 0 && dy == 0)
        return ;

 // must be a complex line so use bresenhams algorithm
    else    {

// swap delta x and delta y depending upon slop of line

        if(dy > dx) {
            temp = dx ;
            dx = dy ;
            dy = temp ;
            interchange = 1 ;
        }

// initialise the error term to compensate for non-zero intercept

        error = (dy << 1) - dx ;    // (2 * dy) - dx

// main loop
        for(i = 1; i <= dx; i++)    {
            WriteAPixel(x, y, Colour);

            while(error >= 0)   {
                if(interchange == 1)
                    x += s1 ;
                else
                    y += s2 ;

                error -= (dx << 1) ;    // times 2
            }

            if(interchange == 1)
                y += s2 ;
            else
                x += s1 ;

            error += (dy << 1) ;    // times 2
        }
    }
}


void Circle(int Xin, int Yin, int rad, int Colour, int ShouldFill)
{
	if(ShouldFill != 0){
		int r2 = rad * rad;
		int area = r2 << 2;
		int rr = rad << 1;
		int i;
		for (i = 0; i < area; i++)
		{
		    int tx = (i % rr) - rad;
		    int ty = (i / rr) - rad;

		    if (tx * tx + ty * ty <= r2)
		        WriteAPixel(Xin + tx, Yin + ty, Colour);
		}
	}else{
		int x = rad;
		int y = 0;
		int err = 0;

		while (x >= y)
		{
			WriteAPixel(Xin + x, Yin + y, Colour);
			WriteAPixel(Xin + y, Yin + x, Colour);
			WriteAPixel(Xin - y, Yin + x, Colour);
			WriteAPixel(Xin - x, Yin + y, Colour);
			WriteAPixel(Xin - x, Yin - y, Colour);
			WriteAPixel(Xin - y, Yin - x, Colour);
			WriteAPixel(Xin + y, Yin - x, Colour);
			WriteAPixel(Xin + x, Yin - y, Colour);

			if (err <= 0)
			{
				y += 1;
				err += 2*y + 1;
			}
			if (err > 0)
			{
				x -= 1;
				err -= 2*x + 1;
			}
		}
	}
}





/*
 * Layout of Corners for Rounded Edges
 * 	_____
 * |1	2|
 * |	 |
 * |3___4|
 *
 */

void FilledRoundedEdges(int Xin, int Yin, int rad, int Colour, int WhichCorner){
	int i;
	for(i = 0; i< rad ; i++){
		int x = i;
		int y = 0;
		int err = 0;

		while (x >= y)
		{
			if(WhichCorner == 1){
				WriteAPixel(Xin - x - 1 , Yin - y - 1 ,Colour);
				WriteAPixel(Xin - y - 1, Yin - x - 1, Colour);
				Line(Xin, Yin,Xin - x - 1, Yin - y - 1,Colour);
				Line(Xin, Yin,Xin - y - 1, Yin - x - 1, Colour);
			}else if(WhichCorner == 2){
				WriteAPixel(Xin + x + 1, Yin - y - 1, Colour);
				WriteAPixel(Xin + y + 1, Yin - x - 1, Colour);
				Line(Xin, Yin,Xin + x + 1, Yin - y - 1, Colour);
				Line(Xin, Yin,Xin + y + 1, Yin - x - 1, Colour);
			}else if(WhichCorner == 3){
				WriteAPixel(Xin - y - 1, Yin + x +1, Colour);
				WriteAPixel(Xin - x - 1, Yin + y +1, Colour);
				Line(Xin, Yin,Xin - y - 1, Yin + x+1, Colour);
				Line(Xin, Yin,Xin - x - 1, Yin + y+1, Colour);
			}else if(WhichCorner == 4){
				WriteAPixel(Xin + x + 1, Yin + y + 1, Colour);
				WriteAPixel(Xin + y + 1, Yin + x + 1, Colour);
				Line(Xin, Yin,Xin + x + 1, Yin + y + 1, Colour);
				Line(Xin, Yin,Xin + y + 1, Yin + x + 1, Colour);
			}
			if (err <= 0)
			{
				y += 1;
				err += 2*y + 1;
			}
			if (err > 0)
			{
				x -= 1;
				err -= 2*x + 1;
			}
		}
	}
}


void SkinnyRoundedEdges(int Xin, int Yin, int rad, int Colour, int WhichCorner){
	int x = rad;
	int y = 0;
	int err = 0;
	Xin++;
	Yin++;

	while (x >= y)
	{
		if(WhichCorner == 1){
			WriteAPixel(Xin - x, Yin - y, Colour);
			WriteAPixel(Xin - y, Yin - x, Colour);
		}else if(WhichCorner == 2){
			WriteAPixel(Xin + x, Yin - y,Colour);
			WriteAPixel(Xin + y, Yin - x, Colour);
		}else if(WhichCorner == 3){
			WriteAPixel(Xin - y, Yin + x, Colour);
			WriteAPixel(Xin - x, Yin + y, Colour);
		}else if(WhichCorner == 4){
			WriteAPixel(Xin + x, Yin + y, Colour);
			WriteAPixel(Xin + y, Yin + x, Colour);
		}

		if (err <= 0)
		{
			y += 1;
			err += 2*y + 1;
		}
		if (err > 0)
		{
			x -= 1;
			err -= 2*x + 1;
		}
	}
}

/*
 * Layout of Corners for Rounded Edges
 * 	_____
 * |1	2|
 * |	 |
 * |3___4|
 *
 */
//TOFDO



void DrawRoundedRectangle(int Xstart, int Ystart, int Xstop, int Ystop, int Radius, int Colour, int ShouldFill)
{
	if(Ystart > Ystop){
		int temp = Ystart;
		Ystart = Ystop;
		Ystop = temp;
	}
	if(Xstart > Xstop){
		int temp = Xstart;
		Xstart = Xstop;
		Xstop = temp;
	}
	if(ShouldFill != 0){
		DrawRectangle(Xstart+Radius,Ystart, Xstop-Radius, Ystart+Radius , Colour,1);
		DrawRectangle(Xstart+Radius,Ystop-Radius, Xstop-Radius, Ystop , Colour,1);
		DrawRectangle(Xstart, Ystart+Radius, Xstop, Ystop-Radius, Colour, 1);
		FilledRoundedEdges(Xstart+Radius, Ystart+Radius, Radius, Colour, 1); //Top Left Corner Denoted by 1
		FilledRoundedEdges(Xstop-Radius, Ystart+Radius, Radius, Colour, 2); //Top Left Corner Denoted by 1
		FilledRoundedEdges(Xstart+Radius, Ystop-Radius, Radius, Colour, 3);
		FilledRoundedEdges(Xstop-Radius, Ystop-Radius, Radius, Colour, 4);
	}else{
		SkinnyRoundedEdges(Xstart+Radius, Ystart+Radius, Radius, Colour, 1); //Top Left Corner Denoted by 1
		SkinnyRoundedEdges(Xstop-Radius, Ystart+Radius, Radius, Colour, 2); //Top Left Corner Denoted by 1
		SkinnyRoundedEdges(Xstart+Radius, Ystop-Radius, Radius, Colour, 3);
		SkinnyRoundedEdges(Xstop-Radius, Ystop-Radius, Radius, Colour, 4);
		DrawVerticalLine(Xstart,Ystart+Radius,Ystop-Radius, Colour);// left side
		DrawVerticalLine(Xstop,Ystart+Radius,Ystop-Radius, Colour);//right side
		DrawHorizontalLine(Xstart+Radius,Xstop-Radius,Ystart, Colour); //Top
		DrawHorizontalLine(Xstart+Radius,Xstop-Radius,Ystop, Colour);	//Bottom
	}
}

void DrawBorderedRoundedRectangle(int Xstart, int Ystart, int Xstop, int Ystop, int BorderWidth, int Radius, int BorderColour, int FillColour)
{
	if(Ystart > Ystop){
		int temp = Ystart;
		Ystart = Ystop;
		Ystop = temp;
	}
	if(Xstart > Xstop){
		int temp = Xstart;
		Xstart = Xstop;
		Xstop = temp;
	}
	DrawRoundedRectangle(Xstart, Ystart, Xstop, Ystop, Radius, BorderColour, 1);
	DrawRoundedRectangle(Xstart+BorderWidth, Ystart+BorderWidth, Xstop-BorderWidth, Ystop-BorderWidth, Radius-BorderWidth, FillColour, 1);
}


void OutGraphicsCharFont1(int x, int y, int fontcolour, int backgroundcolour, int c, int Erase)
{
// using register variables (as opposed to stack based ones) may make execution faster
// depends on compiler and CPU

	register int row, column, theX = x, theY = y ;
	register int pixels ;
	register char theColour = fontcolour  ;
	register int BitMask, theC = c ;

// if x,y coord off edge of screen don't bother

    if(((short)(x) > (short)(XRES-1)) || ((short)(y) > (short)(YRES-1)))
        return ;

// if printable character subtract hex 20
	if(((short)(theC) >= (short)(' ')) && ((short)(theC) <= (short)('~'))) {
		theC = theC - 0x20 ;
		for(row = 0; (char)(row) < (char)(7); row ++)	{

// get the bit pattern for row 0 of the character from the software font
			pixels = Font5x7[theC][row] ;
			BitMask = 16 ;

			for(column = 0; (char)(column) < (char)(5); column ++)	{

// if a pixel in the character display it
				if((pixels & BitMask))
					WriteAPixel(theX+column, theY+row, theColour) ;

				else {
					if(Erase == TRUE)

// if pixel is part of background (not part of character)
// erase the background to value of variable BackGroundColour

						WriteAPixel(theX+column, theY+row, backgroundcolour) ;
				}
				BitMask = BitMask >> 1 ;
			}
		}
	}
}
void DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, int Colour, int ShouldFill){
	Line(x1,y1,x2,y2,Colour);
	Line(x1,y1,x3,y3,Colour);
	Line(x2,y2,x3,y3,Colour);
	if(ShouldFill != 0){
		Fill(x1+1,y1+3,Colour,Colour);
	}
}

void DrawPlayTriangle(int x1,int y1,int Colour){
	int x2,y2,x3,y3;
	x2 = x1+60;
	y2 = y1+45;
	x3 = x1;
	y3 = y1+90;
	DrawTriangle(x1,y1,x2,y2,x3,y3, Colour, TRUE);
	Fill(x1+1,y1+3,Colour,Colour);
}

void DrawPlayTriangleBack(int x1,int y1,int Colour){
	int x2,y2,x3,y3;
	x2 = x1-60;
	y2 = y1+45;
	x3 = x1;
	y3 = y1+90;
	DrawTriangle(x1,y1,x2,y2,x3,y3, Colour, FALSE);
	Fill(x1-1,y1+3,Colour,Colour);

}

void DrawAdvanceIcon(int x1,int y1,int Colour){
	DrawPlayTriangle(x1,y1,Colour);
	DrawRectangle(x1+75, y1, x1+60 , y1 + 90, Colour, TRUE);
}
void DrawRetreatIcon(int x1,int y1,int Colour){
	DrawPlayTriangleBack(x1,y1,Colour);
	DrawRectangle(x1-75, y1, x1-60 , y1 + 90, Colour, TRUE);
}


void OutGraphicsCharFont2(int x, int y, int colour, int backgroundcolour, int c, int Erase)
{
	register int 	row,
					column,
					theX = x,
					theY = y ;
	register int 	pixels ;
	register char 	theColour = colour  ;
	register int 	BitMask,
					theCharacter = c,
					j,
					theRow, theColumn;


    if(((short)(x) > (short)(XRES-1)) || ((short)(y) > (short)(YRES-1)))  // if start off edge of screen don't bother
        return ;

	if(((short)(theCharacter) >= (short)(' ')) && ((short)(theCharacter) <= (short)('~'))) {			// if printable character
		theCharacter -= 0x20 ;																			// subtract hex 20 to get index of first printable character (the space character)
		theRow = FONT2_YPIXELS;
		theColumn = FONT2_XPIXELS;

		for(row = 0; row < theRow ; row ++)	{
			pixels = Font10x14[theCharacter][row] ;		     								// get the pixels for row 0 of the character to be displayed
			BitMask = 512 ;							   											// set of hex 200 i.e. bit 7-0 = 0010 0000 0000
			for(column = 0; column < theColumn;   )  	{
				if((pixels & BitMask))														// if valid pixel, then write it
					WriteAPixel(theX+column, theY+row, theColour) ;
				else {																		// if not a valid pixel, do we erase or leave it along (no erase)
					if(Erase == TRUE)
						WriteAPixel(theX+column, theY+row, backgroundcolour) ;
					// else leave it alone
				}
					column ++ ;
				BitMask = BitMask >> 1 ;
			}
		}
	}
}


