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
	std::string textFilePath = std::filesystem::current_path().string() + "\\textfile\\";
	std::string netcdfPath = std::filesystem::current_path().string() + "\\netcdf\\";
	std::vector<std::string> paths; //vector to store netcdf paths found inside of a file dir
	std::vector<infoNode> pathInfo; //vector of info nodes that will contain the information of each flash event in a netcdf file
public: 
	netcdf(); //default constructor
	void downloadNetCDFs(Aws::Client::ClientConfiguration& clientConfig); //function to download netcdfs from aws
	void deleteNetCDFs(); //function to delete all netCDFs in netcdfPath
	std::string getNetCDFDir(); //funciton to return the directory of the netcdf's
	void getNetCDFDirContents(); //function to create a vector of netcdf filepaths that reside in the netcdfPath
	void printNetCDFpaths(); //funciton to print all of the files in the paths vector
	std::vector<std::string> getPaths(); //function to return the vector containing all of the netcdf files
	void getStormPathInfo(std::ofstream &myfile); //function to process the files in the netcdf directory and push all infonodes to netcdf class. 
	void printAllInfoNodes(); //function to print values from infoNodes
	std::vector<infoNode> getInfoVector(); //function to return the infoNode vector
	std::string getTextPath(); //funciton to return directory of textfile
};
/**
* class infoNode is a storage container that can be vectorized to provide information about flashes 
* at particular latitudes and longitudes for a given file date
*/
class infoNode {
private:
	std::string flashDate = "19700101"; //datestamp representing standard Jan. 1 1970
	std::vector<double> flashlats; //represents latitude of all flash events within bounding box
	std::vector<double> flashlons; //represents longitude of all flash events within bounding box
	std::vector<int> flashStrength; //mJ
	std::vector<int> flashQuality; //flashquality 0-3
	int flashCount = 0; //count of number of flashes pushed to infoNode

public: 
	infoNode(); //default constructor
	void pushFlashLat(const double& latitude);
	void pushFlashLon(const double& longitude);
	void pushFlashDate(const std::string& path);
	void pushFlashStrength(const int& strength);
	void pushFlashQuality(const int& quality);
	int getFlashCount();
	std::string getFlashDate();
	std::vector<double> getFlashLats();
	std::vector<double> getFlashLons();
	std::vector<int> getFlashQuality();
	std::vector<int> getFlashStrength(); 
};
#endif
