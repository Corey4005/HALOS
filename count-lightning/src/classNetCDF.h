#ifndef NETCDF
#define NETCDF
#include <string>
#include <filesystem>
#include "classInterpolate.h"
#include "classDatetime.h"
#include "awsS3.h"
#include <netcdf>

/**
* Header file for classNetCDF
* Purpose: manages netcdf files inside a directory, which means reading and writing new output files from a given set of inputs. 
*/
class netcdf : public Datetime{
private: 
	std::string netcdfPath = std::filesystem::current_path().string() + "\\netcdf\\";
	std::vector<std::string> paths; //vector to store netcdf paths found inside of a file dir
public: 
	netcdf(); //default constructor
	void downloadNetCDFs(Aws::Client::ClientConfiguration& clientConfig); //function to download netcdfs from aws
	void deleteNetCDFs(); 
	std::string getNetCDFDir(); //funciton to return the directory of the netcdf's
	void getNetCDFDirContents(); //function to create a vector of netcdf filepaths that reside in the netcdfPath
	void printNetCDFpaths(); //funciton to print all of the files in the paths vector
	std::vector<std::string> getPaths(); //function to return the vector containing all of the netcdf files
	

};
#endif
