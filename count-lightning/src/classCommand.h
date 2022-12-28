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
	std::vector<std::string> contents;

public: ;
	Command(); //default constructor
	void fillTimeVector(); //fills timesArray with timestamps
	void printTimeVector(); //function to print all values from time vector
	void deleteNetCDFs(); //function to delete all files in the netcdf folder
	void downloadNetCDFs(Aws::Client::ClientConfiguration &clientConfig); //funciton to download all files in timesarray to netcdf folder
	std::string getcwd(); //function to return the current working directory 
	std::vector<std::string> listDirContents(const std::string& path); //function to create a dynamic list of filepaths to netcdf files
	
	const std::string bucket = "noaa-goes16";
	const std::string product = "GLM-L2-LCFA";
	const std::string filestart = "OR_GLM-L2-LCFA_G16_"; //represents file start path
};
#endif
