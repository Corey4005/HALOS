#include "classInterpolate.h"
#include "classDatetime.h"
#include "classCommand.h"
#include <iostream>
#include <string>
#include <vector>
#include <netcdf> 
#include <fstream>
#include <filesystem>
#include <iostream>
#include "awsS3.h"
int main() {
	// Initialize the AWS SDK
	Aws::SDKOptions options;
	Aws::InitAPI(options);

	

	// Create a Command object to download files from a bucket
	Command obj;

	// Set the client configuration to use environment variables
	Aws::Client::ClientConfiguration clientConfig;

	// Set the location for the object
	obj.setLocation(30.30, -55.50, 30.86, -55.11);

	// Calculate the distance, speed, and number of points for the object
	obj.calculateDistance();
	obj.calculateSpeedPerHour(3);
	obj.calculate20SecondDistance();
	obj.calculateNpoints();
	obj.interpolateLatLons();

	// Set the date and time for the object
	obj.setDate(2021, 5, 20);
	obj.setTime(0, 0, 0);
	obj.set_dYear();

	// Fill the time vector with a datestamp for each nPoint and 
	// download the corresponding NetCDF files from s3
	obj.fillTimeVector();

	/*obj.downloadNetCDFs(clientConfig);*/ //<- uncomment to download netcdf files
	// Delete the downloaded NetCDF files
	
	//create a list in paths object containing all of the netcdfs in the current netcdf directory
	obj.getNetCDFDirContents();

	//print the netCDF paths
	/*obj.printNetCDFpaths(); */
	
	//create a test object to open netcdf file 
	std::vector<std::string> path = obj.getPaths(); 
	std::string test = path[0];
	std::cout << test << std::endl;

	netCDF::NcFile dataFile(test, netCDF::NcFile::read);

	//here we will get inquiries of the data
	auto vars = dataFile.getVars(); //variable names
	auto atts = dataFile.getAtts(); //attribute names
	auto attCount = dataFile.getAttCount(); //number of attributes - store metadata of data and files. if temp is a variable, its attribute might be "units"-degreesC
	auto dimCount = dataFile.getDimCount(); //number of dims - Dimensions are used to define the shape of data in netCDF. 
	auto groupCount = dataFile.getGroupCount(); //number of groups - groups are integers that describe how variables are grouped together. Provides an id to group
	auto typeCount = dataFile.getTypeCount(); //number of types 


	//print the information about the file
	std::cout << "there are " << attCount << " attributes in the file" << std::endl; 
	std::cout << "there are " << dimCount << " dimenstions in the file" << std::endl;
	std::cout << "there are " << groupCount << " groups in the file" << std::endl; //there are 0 groups in this file
	std::cout << "there are " << typeCount << " types in the file" << std::endl;  //there are 0 types in this file
	std::cout << std::endl; 

	//here we can print the variables 
	for (std::multimap<std::string, netCDF::NcVar>::iterator itr = vars.begin(); itr != vars.end(); itr++) {
		std::cout << "Variable: " << itr->first << std::endl;
	}
	
	//here we can print the attributes
	for (std::multimap<std::string, netCDF::NcGroupAtt>::iterator itr = atts.begin(); itr != atts.end(); itr++) {
		std::cout << "Attribute: " << itr->first << std::endl;
	}


	
	//obj.deleteNetCDFs(); //<-function deletes all netcdf data in the folder
	// Shut down the AWS SDK
	Aws::ShutdownAPI(options);

	return 0;
}
