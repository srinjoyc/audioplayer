#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <lib/gps.h>

#define GPS_Control (*(volatile unsigned char *)(0x84000210))
#define GPS_Status (*(volatile unsigned char *)(0x84000210))
#define GPS_TxData (*(volatile unsigned char *)(0x84000212))
#define GPS_RxData (*(volatile unsigned char *)(0x84000212))
#define GPS_Baud (*(volatile unsigned char *)(0x84000214))

#define TRUE 1
#define FALSE 0

void initGPS(void)
{
// set up 6850 Control Register to utilise a divide by 16 clock,
// set RTS low, use 8 bits of data, no parity, 1 stop bit,0010101
// transmitter interrupt disabled
	GPS_Control = 0x03;
	GPS_Control = 0x15;
// program baud rate generator to use 9600 baud (larger than 0b100)
	GPS_Baud = 0x05 ;
}


int putcharGPS(int c)
{
// poll Tx bit in 6850 status register. Wait for it to become '1'
// write 'c' to the 6850 TxData register to output the character
	while(GPS_Status && 0x02 != 0x02){

	}
	GPS_TxData = c;
return c ; // return c
}


int getcharGPS( void )
{
// poll Rx bit in 6850 status register. Wait for it to become '1'
// read received character from 6850 RxData register.
	while((GPS_Status & 0x01) != 0x01){
	}
	int temp = GPS_RxData;

	return temp;
}


// the following function polls the 6850 to determine if any character
// has been received. It doesn't wait for one, or read it, it simply tests
// to see if one is available to read
int gpsTestForReceivedData(void)
{
// Test Rx bit in 6850 serial comms chip status register
// if RX bit is set, return TRUE, otherwise return FALSE
	int boolean;
	if((GPS_Status & 0x01) == 0x01){
		boolean = TRUE;
	}
	else
		boolean = FALSE;
	return boolean;
}

void findGPRMC(void){
	while('$'!=getcharGPS()){//$26
	}
	if('G'==getcharGPS()){//G71
		if('P'==getcharGPS()){//P80
			if('R'==getcharGPS()){//82 R
				if('M'==getcharGPS()){//M77
					if('C'==getcharGPS()){//C67
						if(','==getcharGPS()){//,44
							return;
						}
					}
				}
			}
		}
	}
	findGPRMC();
	return;
}

void getDateTimeCoordSpeed(char * date, int * time, char * longitude, char * ns, char * latitude, char * ew, char * speed){
	//using the GPRMC data
	findGPRMC();
	int commaNum;
	unsigned char *word;
	word = (char *) malloc(sizeof(char)*10);
	unsigned char temp;
	int i;
	int nextComNum;
	//there are 9 data that is important rest are useless
	for(commaNum = 0; commaNum<9; commaNum++){
		//parse 1 word and exit when reach to comma
		do{
			temp = getcharGPS();
			if(temp != ','){
				word[i] = temp;
				i++;
			}
			else{
				nextComNum = commaNum + 1;
				word[i] = '\0';
			}
		}while(temp!= ',');
		// assign word to pointer appropriately

		if(commaNum ==0){
			int UTC;
			UTC = (int) strtol(word, (char **)NULL, 10);
			int PST;
			if(UTC>80000){
				PST = UTC - 80000;
			}
			else{
				PST = 240000 + UTC - 80000;
			}
			*time = PST;
			//printf("PST: %06d\n", PST);
		}
		else if(commaNum ==2){
			if(latitude != NULL)
				strcpy(latitude,word);
		}
		else if(commaNum ==3){
			if(ns != NULL)
				strcpy(ns,word);
		}
		else if(commaNum ==4){
			if(longitude != NULL)
				strcpy(longitude,word);
		}
		else if(commaNum ==5){
			if(ew != NULL)
				strcpy(ew,word);
		}
		else if(commaNum ==6){
			if(speed != NULL)
				strcpy(speed,word);
		}
		else if(commaNum ==8){
			if(date != NULL)
				strcpy(date,word);
		}
	}
	free(word);
}
