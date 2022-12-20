#include "classInterpolate.h"
#include "classDatetime.h"
#include "classCommand.h"
#include "awsS3.h"
#include <iostream>
#include <string>
#include <vector>
#include <netcdf> //YAY WE GOT THE NETCDF FILES FROM VCPKG!!
#include <fstream>



int main() {
	Aws::SDKOptions options;
	Aws::InitAPI(options);
	std::cin.get();
	//demonstrating how to look for objects in a bucket

	Command obj; //create a storm object to get files for

	
	Aws::Client::ClientConfiguration clientConfig; //set the client config to set environment variables 


	obj.setLocation(30.30, -55.50, 30.86, -55.11);
	obj.calculateDistance();
	obj.calculateSpeedPerHour(3);
	obj.calculate20SecondDistance();
	obj.calculateNpoints();
	obj.interpolateLatLons();
	obj.setDate(2021, 5, 20);
	obj.setTime(0, 0, 0);
	obj.set_dYear(); //day of year to get data from 
	obj.fillTimeVector();
	
	int number = obj.getNpoints();
	
	//2021:05:20:00:00:20
	std::string year = obj.timesArray[0].substr(0, 4);
	std::string dy = obj.checkdYear(); 
	std::string day = obj.timesArray[0].substr(8, 2);
	std::string hour = obj.timesArray[0].substr(11, 2);
	std::string minute = obj.timesArray[0].substr(14, 2);
	std::string second = obj.timesArray[0].substr(17, 2);
	const char * tsec = "0";
	std::string date = year + dy + hour + minute + second + tsec; 
	std::string bucket = "noaa-goes16";
	std::string prefix = "GLM-L2-LCFA/" + year + "/" + dy + "/" + hour;
	
	findObject(bucket, prefix, date, clientConfig);
	Aws::ShutdownAPI(options); //shutdown the api
}