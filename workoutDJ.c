//#include <stdio.h>
//#include "lib/TouchScreenDriver.h"
//#include "lib/GUI.h"
//#include "lib/gps.h"
//
//typedef enum{
//
//	StartScreen,
//	MenuScreen,
//	MetricScreen,
//	PlaybackScreen
//
//} Display;
//
//
//int main()
//{
//	printf("hi\n");
//	Init_Touch();
//	printf("hi2\n");
//	Point r;
//
//	int count = 0;
//
//	//TODO: init memory for the song name and artist to be retrieved by playback module
//
//	//init memory for data received from GPS sizes yaken from gps.h getDateTimeCoordSpeed())
//	char *date = malloc(sizeof(char)*10);
//	int time = malloc(sizeof(int));
//	char *longitude = malloc(sizeof(char)*10);
//	char *ns = malloc(sizeof(char)*10);
//	char *latitude = malloc(sizeof(char)*10);
//	char *ew = malloc(sizeof(char)*10);
//	char *speed = malloc(sizeof(char)*10);
//
//	Display state = StartScreen;
//	DisplayStart();
//
//	while(1){
//
//		switch(state){
//
//			case StartScreen:
//
//				r = GetPress();
//
//				if((r.x >= 200 & r.x <= 600) & (r.y >= 120 & r.y <=360)){
//					DisplayMenu();
//					state = MenuScreen;
//				}
//
//				break;
//
//			case MenuScreen:
//
//				r = GetPress();
//
//				if(r.x >= 200 & r.x <= 600){
//
//					if(r.y >= 96 & r.y <=192){
//						//DisplayPlayback();
//						state = PlaybackScreen;
//						count = 0;
//					}
//
//					if(r.y >= 288 & r.y <=384){
//						//DisplayMetric();
//						state = MetricScreen;
//						count = 0;
//					}
//
//				}
//
//				break;
//
//			case MetricScreen:
//
//				count ++;
//
//				if( count >= 100000){
//					count =0;
//					//UPDATE!!
//					getDateTimeCoordSpeed(date, time, longitude, ns, latitude, ew, speed);
//					UpdateTime(time);
//				}
//
//				if(ScreenTouched()){
//					//doing it this way may result in it hanging if it does it is because ity is taking to long to get into the GetPress func (possible not likely: a quick tap generates six different touch events)
//
//					r = GetPress();
//
//					if(r.x <= 100 & r.y <= 100){
//						//DisplayMenu();
//						state = MenuScreen;
//						break;
//					}
//
//				}
//
//				break;
//
//			case PlaybackScreen:
//
//				count ++;
//
//				if( count >= 100000){
//					count =0;
//					//UPDATE!!
//					getDateTimeCoordSpeed(date, time, longitude, ns, latitude, ew, speed);
//					UpdateTime(time);
//					//updatefooter
//					//updateheader
//				}
//
//				if(ScreenTouched()){
//
//					r = GetPress();
//
//					if(r.x <= 100 & r.y <= 100){
//						DisplayMenu();
//						state = MenuScreen;
//						break;
//					}
//
//
//					if(r.y >= 200){
//
//						if(r.x <= 200){
//							//play previous song
//							//UpdateSongInfo();
//						}
//						else if(r.x >= 250 & r.x <= 550){
//							//pause/play playback
//						}
//						else if(r.x >= 600){
//							//play next song
//							//UpdateSongInfo();
//						}
//
//					}
//				}
//
//				break;
//
//			default:
//				DisplayStart();
//				state = StartScreen;
//
//				break;
//		}
//	}
//}
//
