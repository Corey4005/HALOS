#include "classCommand.h"
#include <string>
#include <vector>
#include <iostream>

Command::Command() {
	//default constructor
}

void Command::getUniqueHours() { //start here next week
	/*int number = getNpoints();
	for (int i = 0; i < number; i++) {

		timesArray[i].substr(11, 1); 
	}*/
}

void Command::fillTimeVector() {
	int number = getNpoints();

	for (int i = 0; i < number; i++) {
		secTimeDelta(20);
		timesArray.push_back(getDateStamp());
	}
}

void Command::printTimeVector() {
	int number = getNpoints();
	for (int i = 0; i < number; i++) {
		std::cout << timesArray[i] << std::endl;
	}
}
std::string Command::createDownloadStrings() {

	std::string s3 = bucket + "/" + product + "/" + std::to_string(year) + "/" + std::to_string(dYear) + "/";
	return s3; 
}

