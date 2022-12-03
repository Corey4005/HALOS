#ifndef CLASSDATE_H
#define CLASSDATE_H
#include "classInterpolate.h"
#include <string>
/* declaration file for class Distance class
*
*/
class Datetime {
private:
	int maxLeapDays[12] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }; 
	int maxCommonDays[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	bool leapYear = false;

public:
	int year = 1970; 
	int month = 1;
	int day = 1;
	int hour = 0;
	int minute = 0;
	int second = 0;
	int* daysPtr = nullptr;// a ptr to get the maximum number of days for a month depending on if it is a leap year or not. 
	int dYear = 1; // default day of year for January 1, 1970
	std::vector<std::string> timesArray;
	Datetime(); 
	Datetime(int y, int mo, int d);
	int setYear(int y);
	int setMonth(int mo);
	int setDay(int d, int mo);
	int setHour(int h);
	void setDate(int y, int mo, int d);
	void setTime(int h, int s, int mi);
	void set_dYear();  
	void secTimeDelta(int sec);
	std::string checkMonth(); 
	std::string checkDay(); 
	std::string checkMin(); 
	std::string checkSec();
	std::string getDateStamp();

};
#endif

