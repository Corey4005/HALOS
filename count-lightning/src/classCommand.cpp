#include "classCommand.h"
#include <string>
#include <vector>
#include <iostream>
#include <filesystem>
#include "awsS3.h"


Command::Command() {
	//default constructor
}

void listDirContents(const std::string& path) {

	for (const auto& entry : std::filesystem::directory_iterator(path)) {
		contents.push_back(entry.path().filename().string());
	}
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
void Command::downloadNetCDFs(Aws::Client::ClientConfiguration &clientConfig) {
	int number = getNpoints();
	for (int i = 0; i < number; i++) {
		std::string year = timesArray[i].substr(0, 4);
		std::string dy = checkdYear();
		std::string day = timesArray[i].substr(8, 2);
		std::string hour = timesArray[i].substr(11, 2);
		std::string minute = timesArray[i].substr(14, 2);
		std::string second = timesArray[i].substr(17, 2);
		const char* tsec = "0";
		std::string date = year + dy + hour + minute + second + tsec;
		std::string prefix = "GLM-L2-LCFA/" + year + "/" + dy + "/" + hour;
		findObject(bucket, prefix, date, clientConfig, true);
	}
}
void Command::deleteNetCDFs() {
	std::string netCDFPath = cwd + "\\netcdf\\"; 
	for (const auto& entry : std::filesystem::directory_iterator(netCDFPath)) {
		if (entry.is_regular_file()) {
			std::filesystem::remove(entry.path());
			std::cout << entry.path() << " removed!" << std::endl;
		}
	}
}

std::string Command::getcwd() {
	return cwd;
}