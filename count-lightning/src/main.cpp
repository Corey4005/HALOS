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
	obj.downloadNetCDFs(clientConfig);

	// Delete the downloaded NetCDF files
	//obj.deleteNetCDFs(); //<-function deletes all netcdf data in the folder

	// Shut down the AWS SDK
	Aws::ShutdownAPI(options);

	return 0;
}
