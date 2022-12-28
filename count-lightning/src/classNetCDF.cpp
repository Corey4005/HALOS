#include "classNetCDF.h"
#include "classInterpolate.h"
#include "classDatetime.h"
#include "awsS3.h"
#include <netcdf>

netcdf::netcdf() { //default constructor

}
std::string netcdf::getNetCDFDir() {
	return netcdfPath;
}

void netcdf::downloadNetCDFs(Aws::Client::ClientConfiguration& clientConfig) {
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
void netcdf::deleteNetCDFs() {
	
	for (const auto& entry : std::filesystem::directory_iterator(getNetCDFDir())) {
		if (entry.is_regular_file()) {
			std::filesystem::remove(entry.path());
			std::cout << entry.path() << " removed!" << std::endl;
		}
	}
}
void netcdf::getNetCDFDirContents() {
	std::vector<std::string> path = getPaths();
	for (const auto& entry : std::filesystem::directory_iterator(getNetCDFDir())){
		paths.push_back(entry.path().string());
	}
}

void netcdf::printNetCDFpaths() {
	for (int i = 0; i < getPaths().size(); i++) {
		std::cout << paths[i] << std::endl;
	}
}

std::vector<std::string> netcdf::getPaths() {
	return paths;
}

