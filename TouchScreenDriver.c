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

#include <stdio.h>
#include "lib/TouchScreenDriver.h"

void Init_Touch(void)
{
	// Program 6850 and baud rate generator to communicate with touchscreen
	// send touchscreen controller an "enable touch" command

	TouchScreen_Baud = 7;	//baudrate = 9600
	TouchScreen_Control = 21;
	printf("Init: %x touch baud c\n", TouchScreen_Baud);
	while((TouchScreen_Status >> 1) % 2 == 0){
		printf("TOUCHSTAT: %x", TouchScreen_Status);
	}
	printf("Init: %x touch status\n", TouchScreen_Status); //binary 00010101  disable RX andTX interrupts
								//set RTS LOW, 8 bit data no parity one stop bit
								//clock divide by 16
	while((TouchScreen_Status >> 1) % 2 == 0);
	printf("Init: %x touch status2\n", TouchScreen_Status);
								//enable touch
	TouchScreen_TxData = 0x55; //Synch bit
	printf("Init: %x txData1\n", TouchScreen_TxData);
	while((TouchScreen_Status >> 1) % 2 == 0); // wait for transfer
	TouchScreen_TxData = 1;    //size
	while((TouchScreen_Status >> 1) % 2 == 0); // wait for transfer
	printf("Init: %x txData2\n", TouchScreen_TxData);
	TouchScreen_TxData = 0x12; //command data
	while((TouchScreen_Status >> 1) % 2 == 0); // wait for transfer
	printf("Init: %x txData3\n", TouchScreen_TxData);

	return;

}

/*****************************************************************************
** test if screen touched
*****************************************************************************/
int ScreenTouched( void )
{
	// return TRUE if any data received from 6850 connected to touchscreen
	// or FALSE otherwise
	if(TouchScreen_Status % 2)
		printf("TOUCHED\n");
	return TouchScreen_Status % 2;
}

/*****************************************************************************
** wait for screen to be touched
*****************************************************************************/
void WaitForTouch()
{
	while(!ScreenTouched())
		;
}


/*****************************************************************************
* This function waits for a touch screen press event and returns X,Y coord
*****************************************************************************/
Point GetPress(void)
{
	/*
	while(1){

		while(TouchScreen_Status % 2 == 0);
		//if(TouchScreen_RxData == 0x81)
			//printf("Pen down\n");
		if(TouchScreen_RxData == 0x80)
			printf("Pen up\n");

	}
*/

	Point p1;

	int buffer[5] = {0,0,0,0,0};
	int i;
	// wait for a pen down command then return the X,Y coord of the point
	// calibrated correctly so that it maps to a pixel on screen
	while(buffer[0] != 0x81){
		while(TouchScreen_Status % 2 == 0);
		buffer[0] = TouchScreen_RxData;

	}

	for(i = 1; i<=4; i++){

		while(TouchScreen_Status % 2 == 0);
		buffer[i] = TouchScreen_RxData;


	}


//	p1.x = (buffer[2] <<7) + buffer[1];
//	p1.y = (buffer[4] <<7) + buffer[3];
//
//	p1.x = p1.x * 800;
//	p1.x = p1.x/4096;
//
//	p1.y = p1.y * 480;
//	p1.y = p1.y/4096;


	return p1;
}

/*****************************************************************************
* This function waits for a touch screen release event and returns X,Y coord
*****************************************************************************/
Point GetRelease(void)
{
	Point p1;

	int buffer[5] = {0,0,0,0,0};
	int i;
		// wait for a pen down command then return the X,Y coord of the point
		// calibrated correctly so that it maps to a pixel on screen
	while(buffer[0] != 0x80){
		while(TouchScreen_Status % 2 == 0);
		buffer[0] = TouchScreen_RxData;

	}

	for(i = 1; i<=4; i++){

		while(TouchScreen_Status % 2 == 0);
		buffer[i] = TouchScreen_RxData;

	}


//	p1.x = (buffer[2] <<7) + buffer[1];
//	p1.y = (buffer[4] <<7) + buffer[3];
//
//	p1.x = p1.x * 800;
//	p1.x = p1.x/4096;
//
//	p1.y = p1.y * 480;
//	p1.y = p1.y/4096;
//	printf("POINT %d %d\n", p1.x, p1.y);
	return p1;
}

int main()
{
	Point r;

	printf("Starting..\n");
	Init_Touch();

	r = GetPress();

	printf("X: %d, Y: %d\n", r.x,r.y);
	printf("Finished\n");
}
