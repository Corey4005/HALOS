#include <iostream>
#include "classDatetime.h"
#include "classInterpolate.h"
#include <sstream>
#include <string>
#include <format>

/* Implemetation file for class Datetime.
*
* This is a class to create timestamps that can be modified for calling specific datestrings from AWS. 
* 
*/

Datetime::Datetime() {
	//default constructor
}
Datetime::Datetime(int y, int mo, int d) {
	year = setYear(y);
	month = setMonth(mo);
	day = setDay(d, mo);
}
void Datetime::setDate(int y, int mo, int d) {
	year = setYear(y); 
	month = setMonth(mo);
	day = setDay(d, mo);
}

//void Datetime::set_dYear() { // work here
	//int sum = 0; 
	//for (int i = 0; daysPtr < i; i++)
		//std::cout << i; 
//}
void Datetime::setTime(int h, int s, int mi) {
	hour = setHour(h);
	second = s; 
	minute = mi; 
}
int Datetime::setYear(int y) {
	if (y % 4 == 0) { //checking to see if the year is a leap year
		leapYear = true;
	}
	return y;
}

int Datetime::setMonth(int mo) {
	try { //try block to make sure that months cannot be below 1 or above 13
		if (mo > 12 || mo < 1) {
			throw 1;
		}
	}
	catch (int x) {
		std::cout << "Datetime month value cannot be greater than 12 or less than 1 ERROR NUMBER: " << x << std::endl;
		exit(3);
	}

	return mo; 
}

int Datetime::setDay(int d, int mo) {
	int mValue = mo - 1; 
	try {
		if (leapYear) {
			int maxDay = maxLeapDays[mValue];
			daysPtr = maxLeapDays + mValue;  
			if (d > maxDay || d < 0) {
				throw 1;
			}
		}
		else {
			int maxDay = maxCommonDays[mValue];
			daysPtr = maxCommonDays + mValue;
			if (d > maxDay || d < 0) {
				throw 1;
			}
		}
	}
	catch (int x) {
		std::cout << "Datetime day object cannot be below 1 or greater than number of possible days in month value ERROR NUMBER : " << x << std::endl;
		exit(3);
	}

	return d; 
}

int Datetime::setHour(int h) {
	try { 
		if (h>=24 || h<0) {
			throw 1;
		}
	}
	catch (int x) {
		std::cout << "Datetime hour value cannot be greater than 23 or less than 0 ERROR NUMBER: " << x << std::endl;
		exit(3);
	}

	return h;
}


void Datetime::secTimeDelta(int sec) {
	try {
		if (sec > 60 || sec < 0) {
			throw 1;
		}
	}
	catch (int x) {
		std::cout << "second TimeDelta cannot be above 60 (1 minute in seconds) or less than 0 ERROR NUMBER : " << x << std::endl;
		exit(3);
	}
	if (second == 60) {
		minute++;
		second = 0;
	} if (minute == 60) {
		minute = 0;
		hour++;
	} if (hour == 23) {
		hour = 0;
		day++;
	} 
	second += sec; 
	if (second >= 60) {
		int leftover = second - 60; 
		minute++;
		second = 0 + leftover;
	}
	if (minute == 60) {
		minute = 0; 
		hour++; 
	}
}

std::string Datetime::getDateStamp() {
	std::string mo = std::to_string(month);
	std::string d = std::to_string(day);
	std::string y = std::to_string(year);
	std::string s = std::to_string(second);
	std::string mi = std::to_string(minute);
	std::string h = std::to_string(hour);
	std::string dateStamp = y + ":" + mo + ":" + d + ":" + h + ":" + mi + ":" + s; 
	return dateStamp; 
	
}

