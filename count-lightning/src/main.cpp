#include "classInterpolate.h"
#include "classDatetime.h"
#include "classCommand.h"
#include "awsS3.h"
#include <iostream>
#include <string>
#include <vector>
#include <netcdf> //YAY WE GOT THE NETCDF FILES FROM VCPKG!!



int main() {
	Aws::SDKOptions options;
	Aws::InitAPI(options);


	//demonstrating how to look for objects in a bucket
	Command obj; //create a command object 
	const Aws::String bucket_name = obj.bucket; // get the bucket containing some sample netcdf files
	Aws::Client::ClientConfiguration clientConfig; //set the client config to set environment variables 
	ListObjects(bucket_name, clientConfig); //check the bucket to see if the bucket has files
	Aws::ShutdownAPI(options); //shutdown the api

	obj.setLocation(30.30, -55.50, 30.86, -55.11);
	obj.calculateDistance();
	obj.calculateSpeedPerHour(3);
	obj.calculate20SecondDistance();
	obj.calculateNpoints();
	obj.interpolateLatLons();
	/*obj.printNpoints();*/
	obj.setDate(2021, 5, 20);
	obj.setTime(0, 0, 0);
	obj.set_dYear(); //day of year to get data from 
	obj.fillTimeVector();



	for (int i = 0; i < 540; i++) {
		std::cout << obj.timesArray[i] << std::endl;

		
	}
	
}