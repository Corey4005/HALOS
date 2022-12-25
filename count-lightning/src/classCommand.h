#ifndef CLASS_COMMAND_H
#define CLASS_COMMAND_H
#include "classDatetime.h"
#include "classInterpolate.h"
#include <string>
#include <vector>
#include <filesystem>
#include "awsS3.h"


class Command : public Interpolate, public Datetime {
private:

	
	std::vector<int> hours; 
	std::string cwd = std::filesystem::current_path().string();

public: 
	Command(); //default constructor
	void fillTimeVector(); //fills timesArray with timestamps
	void getUniqueHours(); //function to set vector with unique hours from timestamps
	void printTimeVector(); //function to print all values from time vector
	void deleteNetCDFs(); //function to delete all files in the netcdf folder
	void downloadNetCDFs(Aws::Client::ClientConfiguration &clientConfig); //funciton to download all files in timesarray to netcdf folder
	const std::string bucket = "noaa-goes16";
	const std::string product = "GLM-L2-LCFA";
	const std::string filestart = "OR_GLM-L2-LCFA_G16_"; //represents file start path
};
#endif
