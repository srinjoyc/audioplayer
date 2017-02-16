#ifndef TOUCHSCREENDRIVER_H_
#define TOUCHSCREENDRIVER_H_


#define TouchScreen_Control (*(volatile unsigned char *)(0x84000230))
#define TouchScreen_Status (*(volatile unsigned char *)(0x84000230))
#define TouchScreen_TxData (*(volatile unsigned char *)(0x84000232))
#define TouchScreen_RxData (*(volatile unsigned char *)(0x84000232))
#define TouchScreen_Baud (*(volatile unsigned char *)(0x84000234))

/* a data type to hold a point/coord */
typedef struct { int x, y; } Point ;


void Init_Touch();

/*****************************************************************************
** test if screen touched
*****************************************************************************/
int ScreenTouched();
/*****************************************************************************
** wait for screen to be touched
*****************************************************************************/
void WaitForTouch();

/*****************************************************************************
* This function waits for a touch screen press event and returns X,Y coord
*****************************************************************************/
Point GetPress();

/*****************************************************************************
* This function waits for a touch screen release event and returns X,Y coord
*****************************************************************************/
Point GetRelease(void);

#endif TOUCHSCREENDRIVER_H_
