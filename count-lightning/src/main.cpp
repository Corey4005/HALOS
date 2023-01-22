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
	//Initialize the AWS SDK
	Aws::SDKOptions options;
	Aws::InitAPI(options);

	// Set the client configuration to use environment variables
	Aws::Client::ClientConfiguration clientConfig;

	//get the stormtracks dir
	std::string stormtracks = std::filesystem::current_path().string() + "\\stormtracks\\";

	//iterate through the stormtrack dir and open any files. if no file, break and return 0; 
	int fileCount = 0; //counter to keep track of number of files

	for (const auto& entry : std::filesystem::directory_iterator(stormtracks)) {
		if (entry.is_regular_file()) {
			fileCount++;
			//stormdtrack file
			std::string path = entry.path().string(); 

			//file name
			std::string filename = entry.path().filename().string(); 

			// create the textfilepath
			std::string textFilePath = std::filesystem::current_path().string() + "\\textfile\\";

			//create output file 
			std::ofstream myfile;
			//creating the textfile in the textfile dir
			myfile.open(textFilePath+filename);

			//we will spit out the textfile and then close it with the new header. 
			myfile << "DateStamp (yyyydddhhmmssmm),Latitude (degrees),Flash Longitude (degrees),Flash Strength (Total Mj)" << std::endl;

			//create a stringstream to open the file
			std::ifstream input_file(path);
			
			//create a string line to get each line and process it in the stormfile
			std::string line; 

			//create some variables to store the lats, lons and dates in
			int year, month, day, hour, minute, second; //variables describing the year, month and day of the storm start time
			double startLat, startLon, endLat, endLon; //variables describing the start lon and lat and ending lon and lat

			int lineCount = 0;
			//while there is a line in the file, use a string stream to push them into variables
			while (std::getline(input_file, line)) {
				//if it is the first line, skip it because this is just descriptive headers
				if (lineCount == 0) {
					lineCount++;
				}
				//else get the line and process it
				else { 
					std::stringstream linestream(line);
					std::string value;
					std::string valueArray[6]; //an array to store each value seperated by comma
					int arrayCount = 0;
					while (std::getline(linestream, value, ',')) { //get the value at the ',' seperator and store in array in order
						valueArray[arrayCount] = value; //store the value, order is startStamp, endStamp, startLat, startLon, endLat, endLon
						arrayCount++;

					}
					//fix the start and end timestamp
					std::string delimiter = "-";
					size_t pos = 0;
					int startArray[6]; //represents year, month, day, hour, min, sec
					int index = 0; //index to get where we are in array
					while ((pos = valueArray[0].find(delimiter)) != std::string::npos) {
						startArray[index] = std::stoi(valueArray[0].substr(0, pos));
						valueArray[0].erase(0, pos + delimiter.length());
						index++;
					}
					startArray[5] = std::stoi(valueArray[0].substr(0, 1)); //after erasing all the data and storing it in array, we now can just grab the last thing in valueArray as the sec value
					valueArray[0].erase(0);

					//now we will retrieve the lats and lons needed for the program
					startLat = std::stod(valueArray[2]);
					startLon = std::stod(valueArray[3]);

					if (startLon > 180.0) {
						startLon = startLon - 360.0;
					}

					endLat = std::stod(valueArray[4]);
					endLon = std::stod(valueArray[5]);
					if (endLon > 180.0) {
						endLon = endLon - 360.0;
					}

					//now we will get the times from the array into int objects
					year = startArray[0];
					month = startArray[1];
					day = startArray[2];
					hour = startArray[3];
					minute = startArray[4];
					second = startArray[5];


					Command obj;
					// Set the location for the object
					obj.setLocation(startLat, startLon, endLat, endLon);

					// Calculate the distance, speed, and number of points for the object
					obj.calculateDistance();
					obj.calculateSpeedPerHour(3);
					obj.calculate20SecondDistance();
					obj.calculateNpoints();
					obj.interpolateLatLons();

					// Set the date and time for the object
					obj.setDate(year, month, day);
					obj.setTime(hour, minute, second);
					obj.set_dYear();

					// Fill the time vector with a datestamp for each nPoint and 
					obj.fillTimeVector();
					obj.printNpoints();

					//download the corresponding timeVector files from AWS 
					obj.downloadNetCDFs(clientConfig); //<- comment to stop the download of files (if they are in directory already)

					//create a list object containing all of the netcdfs in the current netcdf directory
					obj.getNetCDFDirContents();

					//go through each file in the list object and create an infonode and extract flash data to text file
					obj.getStormPathInfo(myfile);

					//delete all netcdfs
					obj.deleteNetCDFs(); //delete all the netcdfs in the netcdf folder to conserve memory


				}


				

			}
			myfile.close();
			
		}
		
		if (fileCount == 0) {
			Aws::ShutdownAPI(options);
			std::cout << "There are no storms to process in the " << stormtracks << " directory!" << std::endl;
			return 0;
		}
			
	}
	

	// Shut down the AWS SDK
	Aws::ShutdownAPI(options);
	return 0;
}
