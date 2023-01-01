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
	obj.fillTimeVector();

	//download the corresponding timeVector files from AWS 
	/*obj.downloadNetCDFs(clientConfig); *///<- comment to stop the download of files (if they are in directory already)
	
	//create a list object containing all of the netcdfs in the current netcdf directory
	obj.getNetCDFDirContents();

	//go through each file in the list object and create a info node for each 
	obj.getStormPathInfo(); 

	//print all the info from the netcdf data
	obj.printAllInfoNodes(); 
	/*obj.deleteNetCDFs();*/ //<-comment this function to stop the deletion of all netcdf data in the folder.
	// Shut down the AWS SDK
	Aws::ShutdownAPI(options);

	//get the info node and push the data to a textfile
	std::vector<infoNode> flashInfo = obj.getInfoVector();
	std::ofstream myfile;

	//creating the textfile in the textfile dir
	myfile.open(obj.getTextPath()+"flashdata.txt");

	//file will be comma delimiated for easy excel use
	myfile << "DateStamp (yyyydddhhmmssmm),Latitude (degrees),Flash Longitude (degrees),Flash Strength (Total Mj)" << "\n";
	for (int i = 0; i < obj.getInfoVector().size(); i++) {
		for (int j = 0; j < flashInfo[i].getFlashLats().size(); j++) {
			myfile << flashInfo[i].getFlashDate() << "," << flashInfo[i].getFlashLats()[j] << "," << flashInfo[i].getFlashLons()[j] << "," << flashInfo[i].getFlashStrength()[j] << "\n";
		}
	}
	myfile.close();
	return 0;
}
