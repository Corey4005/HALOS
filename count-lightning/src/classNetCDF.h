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
	friend class infoNode; 
	std::string netcdfPath = std::filesystem::current_path().string() + "\\netcdf\\";
	std::vector<std::string> paths; //vector to store netcdf paths found inside of a file dir
	std::vector<infoNode> flashes; //vector of info nodes that will contain the information of each flash event in a netcdf file
public: 
	netcdf(); //default constructor
	void downloadNetCDFs(Aws::Client::ClientConfiguration& clientConfig); //function to download netcdfs from aws
	void deleteNetCDFs(); 
	std::string getNetCDFDir(); //funciton to return the directory of the netcdf's
	void getNetCDFDirContents(); //function to create a vector of netcdf filepaths that reside in the netcdfPath
	void printNetCDFpaths(); //funciton to print all of the files in the paths vector
	std::vector<std::string> getPaths(); //function to return the vector containing all of the netcdf files
	

};
/**
* class infoNode is a storage container that can be vectorized to provide information about flashes 
* at particular latitudes and longitudes for a given file date
*/
class infoNode {
private:
	double lat = 0.0; //represents latitude of flash event
	double lon = 0.0; //longitude
	int flashDate = 19700101; //datestamp representing standard Jan. 1 1970
	double flashStrength = 0.0; 
public: 
	infoNode(); //default constructor
};
#endif
