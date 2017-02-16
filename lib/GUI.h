/*
 * GUI.h
 *
 *  Created on: 2017-02-09
 *      Author: z2x9a
 */

#ifndef GUI_H_
#define GUI_H_

#include "GraphicsDriver.h"
#include <stdlib.h>


#define WIDE_B_WIDTH 		250
#define WIDE_B_HEIGHT 		100
#define WIDE_B_RADIUS 		15
#define WIDE_B_BORDER 		10
#define WIDE_B_X_TEXTOFFSET	60
#define WIDE_B_Y_TEXTOFFSET	40

#define START_B_X				200
#define	START_B_Y				120
#define START_B_HEIGHT			240
#define START_B_WIDTH			400
#define START_B_X_TEXTOFFSET	105
#define START_B_Y_TEXTOFFSET	120
#define START_TEXT				"Workout DJ Start!"

#define MENU_B_WIDTH			400
#define MENU_B_HEIGHT			96
#define MENU_B_OFFSET_X			200
#define MENU_B_OFFSET_Y			96
#define MENU_B2_OFFSET_Y		288
#define MENU_B1_TEXT			"Play Music"
#define MENU_B2_TEXT			"Check Stats"
#define	MENU_B1_X_TEXTOFFSET	140
#define MENU_B2_X_TEXTOFFSET	130
#define MENU_B1_Y_TEXTOFFSET	45
#define MENU_B2_Y_TEXTOFFSET	45


#define TEXT_KERNING		2

void WideButtonText(int x1, int y1 ,int x2, int y2, int textXoffset, int textYoffset, char* text);

void DisplayText(int x, int y, char* text, int textColour, int backgroundColour);

void DisplayStart();

void DisplayMenu();

void DisplayMetricScreen(char* date, int time, char* longitude, char* latitude, char* speed );

void DisplayBackButton();
void DisplayHeader(int time);
void DisplayFooter(char* longitude, char* latitude, char* speed);

void UpdateFooter(char* longitude, char* latitude, char* speed);

void UpdateSongInfo(char* title, char* artist);
void UpdateTime(int time);

void DisplayPlayback(char* longitude, char* latitude, char* speed, int time);
#endif /* GUI_H_ */
