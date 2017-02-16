/*
 * GUI.c
 *
 *  Created on: 2017-02-09
 *      Author: z2x9a
 */
#include "lib/GUI.h"
#include <stdlib.h>


void WideButtonText(int x1, int y1 ,int x2, int y2, int textXoffset, int textYoffset, char* text){
	DrawBorderedRoundedRectangle( x1,  y1,  x2,  y2, WIDE_B_BORDER, WIDE_B_RADIUS, BLUE, PALE_TURQUOISE);
	//DisplayText(x1+textXoffset, y1 + textYoffset, BLACK, PALE_TURQUOISE, text);
	int j = 0;
	int xMover2 = x1;
	while (text[j]!='\0'){
		OutGraphicsCharFont2(xMover2+textXoffset, y1 + textYoffset, BLACK, PALE_TURQUOISE, (int)text[j], 0);
		xMover2 += FONT2_XPIXELS + TEXT_KERNING;
		j++;
	}
}

void DisplayText(int x, int y, char* text, int textColour, int backgroundColour){
	int j = 0;
	int xMover = x;
	while (text[j]!='\0'){
		OutGraphicsCharFont2(xMover, y, textColour, backgroundColour, (int)text[j], 0);
		xMover += FONT2_XPIXELS + TEXT_KERNING;
		j++;
	}

}


void DisplayStart(){
	WideButtonText(START_B_X, START_B_Y, START_B_X+START_B_WIDTH, START_B_Y+START_B_HEIGHT, START_B_X_TEXTOFFSET, START_B_Y_TEXTOFFSET, START_TEXT);
}

void DisplayMenu(){
	WideButtonText(MENU_B_OFFSET_X, MENU_B_OFFSET_Y, MENU_B_OFFSET_X + MENU_B_WIDTH, MENU_B_OFFSET_Y + MENU_B_HEIGHT,MENU_B1_X_TEXTOFFSET, MENU_B1_Y_TEXTOFFSET, MENU_B1_TEXT);
	WideButtonText(MENU_B_OFFSET_X, MENU_B2_OFFSET_Y, MENU_B_OFFSET_X + MENU_B_WIDTH, MENU_B2_OFFSET_Y + MENU_B_HEIGHT, MENU_B2_X_TEXTOFFSET, MENU_B2_Y_TEXTOFFSET, MENU_B2_TEXT);

}

void DisplayMetricScreen(char* date, int time, char* longitude, char* latitude, char* speed ){
	DrawBorderedRoundedRectangle(100,200,700,380,10,15,BLUE, PALE_TURQUOISE);
	char* timeString;
	sprintf(timeString, "%d", time);
	DisplayBackButton();
	DisplayText(200, 220, date, BLACK, PALE_TURQUOISE);
	DisplayText(350, 220, timeString, BLACK, PALE_TURQUOISE);
	DisplayText(150, 280, "Long: ", BLACK, PALE_TURQUOISE);
	DisplayText(150, 320, "Lat: ",BLACK, PALE_TURQUOISE);
	DisplayText(150, 360, "Speed: ",BLACK, PALE_TURQUOISE);
	DisplayText(340, 30, "Your Stats", BLACK, WHITE);

}

void DisplayBackButton(){
	DrawBorderedRoundedRectangle(0,0,100,100,10,15, BLACK, FIREBRICK);
	DisplayText(30,40,"BACK", BLACK, FIREBRICK);
}

void DisplayHeader(int time){
	DrawRectangle(0,0,800,40,PALE_TURQUOISE, TRUE);
	DrawRectangle(0,40,800,45,BLUE,TRUE);
	UpdateTime(time);
}

void DisplayFooter(char* longitude, char* latitude, char* speed){
	DrawRectangle(0,440,800,480,PALE_TURQUOISE, TRUE);
	DrawRectangle(0,430,800,440,BLUE,TRUE);
	DisplayText(75, 450, "Long: ", BLACK, PALE_TURQUOISE);
	DisplayText(350, 450, "Lat: ",BLACK, PALE_TURQUOISE);
	DisplayText(600, 450, "Speed: ",BLACK, PALE_TURQUOISE);
	UpdateFooter(longitude,latitude,speed);
}

void UpdateFooter(char* longitude, char* latitude, char* speed){
	DrawRectangle(150,450,300,480,PALE_TURQUOISE, TRUE);
	DrawRectangle(410,450,560,480,PALE_TURQUOISE, TRUE);
	DrawRectangle(680,450,800,480,PALE_TURQUOISE, TRUE);
	DisplayText(150, 450, longitude, BLACK, PALE_TURQUOISE);
	DisplayText(410, 450, latitude,BLACK, PALE_TURQUOISE);
	DisplayText(680, 450, speed ,BLACK, PALE_TURQUOISE);
}

void UpdateSongInfo(char* title, char* artist){
	DrawRectangle(200,50,550,200,WHITE, TRUE);
	DisplayText(250,60, title,BLACK, PALE_TURQUOISE);
	DisplayText(250,100, artist ,BLACK, PALE_TURQUOISE);

}
void UpdateTime(int time){
	char* timeString;
	sprintf(timeString, "%d", time);
	DrawRectangle(380,0, 450, 30, PALE_TURQUOISE, TRUE);
	DisplayText(380,10,timeString, BLACK, PALE_TURQUOISE);
}

void DisplayPlayback(char* longitude, char* latitude, char* speed, int time){

	ClearScreen();
	//DrawVerticalLine(200, 0, 480, BLACK);
	//DrawHorizontalLine(0,800,200, BLACK);
	//DrawVerticalLine(250, 0, 480, BLACK);
	//DrawVerticalLine(550, 0, 480, BLACK);
	//DrawVerticalLine(600, 0, 480, BLACK);
	DrawRetreatIcon(140,280,BLACK);
	DrawPlayTriangle(390,280,BLACK);
	DrawAdvanceIcon(670, 280, BLACK);
	DisplayHeader(time);
	DisplayFooter(longitude,latitude,speed);

}







