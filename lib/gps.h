#ifndef GPS_H
#define GPS_H

//need to initialize GPS serial port before using the GPS
void initGPS(void);
// read from GPS
int getcharGPS( void );
//write to GPS
int putcharGPS(int c);
//Test serial port
int gpsTestForReceivedData(void);
//find and get rid of "$GPRMC,"
void findGPRMC(void);
//get specific data from GPS - Need to pass in pointers that can store at least 10 characters (use malloc())
void getDateTimeCoordSpeed(char * date, int * time, char * longitude, char * ns, char * latitude, char * ew, char * speed);

#endif GPS_H
