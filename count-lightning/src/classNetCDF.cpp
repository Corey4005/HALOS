#include "classNetCDF.h"
#include "classInterpolate.h"
#include "classDatetime.h"
#include "awsS3.h"
#include <netcdf>
#include <string>
#include <fstream>
///----------------------------------------------------------------
/// function definitions for netcdf class
///---------------------------------------------------------------

netcdf::netcdf() { //default constructor

}
std::string netcdf::getNetCDFDir() {
	return netcdfPath;
}

void netcdf::downloadNetCDFs(Aws::Client::ClientConfiguration& clientConfig) {
	int number = getNpoints();
	int objectCount = 1;
	for (int i = 0; i < number; i++) {
		std::string year = timesArray[i].substr(0, 4);
		std::string dy = checkdYear();
		std::string day = timesArray[i].substr(8, 2);
		std::string hour = timesArray[i].substr(11, 2);
		std::string minute = timesArray[i].substr(14, 2);
		std::string second = timesArray[i].substr(17, 2);
		const char* tsec = "0";
		std::string date = year + dy + hour + minute + second + tsec;
		std::string prefix = "GLM-L2-LCFA/" + year + "/" + dy + "/" + hour;
		findObject(bucket, prefix, date, clientConfig, true, objectCount, number);
		objectCount++; 
	}
}
void netcdf::deleteNetCDFs() {
	
	for (const auto& entry : std::filesystem::directory_iterator(getNetCDFDir())) {
		if (entry.is_regular_file()) {
			std::filesystem::remove(entry.path());
			std::cout << entry.path() << " removed!" << std::endl;
		}
	}
}
void netcdf::getNetCDFDirContents() {
	std::vector<std::string> path = getPaths();
	for (const auto& entry : std::filesystem::directory_iterator(getNetCDFDir())){
		paths.push_back(entry.path().string());
	}
}

void netcdf::printNetCDFpaths() {
	for (int i = 0; i < getPaths().size(); i++) {
		std::cout << paths[i] << std::endl;
	}
}

std::vector<std::string> netcdf::getPaths() { return paths;}

void netcdf::getStormPathInfo(std::ofstream &myfile) {
	//get the interpolated lats and lons list
	std::vector<double> stormLats = getInterpolatedLats();
	std::vector<double> stormLons = getInterpolatedLons(); 
	
	//test is the paths of the files that we will loop through to process
	int test = getPaths().size(); 

	//loop through each file and process it 
	for (int i = 0; i < test; i++) {
		std::cout << "processing file: " << paths[i].substr(73, 14) << std::endl;
		
		//open the path netcdf
		netCDF::NcFile dataFile(paths[i], netCDF::NcFile::read);

		//create a list of variables to collect
		netCDF::NcVar flashLat, flashLon, flashEnergy, flashQuality;
		flashLat = dataFile.getVar("flash_lat");
		flashLon = dataFile.getVar("flash_lon");
		flashEnergy = dataFile.getVar("flash_energy");
		flashQuality = dataFile.getVar("flash_quality_flag");

		// create a vector conatining the dimensions of the flash objects
		std::vector<netCDF::NcDim> flashLatDims = flashLat.getDims();
		std::vector<netCDF::NcDim> flashLonDims = flashLon.getDims();
		std::vector<netCDF::NcDim> flashEnergyDims = flashEnergy.getDims();
		std::vector<netCDF::NcDim> flashQualityDims = flashQuality.getDims();

		// create arrays to store the data inside that are dynamic, based on the size of the Dim
		double* flashLatData = new double[flashLatDims[0].getSize()];
		double* flashLonData = new double[flashLonDims[0].getSize()];
		int* flashEnergyData = new int[flashEnergyDims[0].getSize()];
		int* flashQualityData = new int[flashQualityDims[0].getSize()];

		//call the getVar() function on NcVar object and store it in the data arrays
		flashLat.getVar(flashLatData);
		flashLon.getVar(flashLonData);
		flashEnergy.getVar(flashEnergyData);
		flashQuality.getVar(flashQualityData);

		//create bounding box for flash events
		double maxLat = stormLats[i] + 5.0;
		double minLat = stormLats[i] - 5.0; 
		double maxLon = stormLons[i] + 5.0;
		double minLon = stormLons[i] - 5.0;

		//create infonode and get information about variables 
		int dimSize = flashLatDims[0].getSize(); 

		//create a node to collect the flash information in
		infoNode* newNode = new infoNode; 

		//push the date to the node
		newNode->pushFlashDate(paths[i]);
		
		//loop through all of the file flash data and check if it is within the bounding box
		for (int j = 0; j<dimSize; j++) {
			double lat = *(flashLatData + j);
			double lon = *(flashLonData + j);

			//if the flash data is within the bounding box, push it to the node
			if (minLat <=  lat && lat <= maxLat && minLon <= lon && lon <= maxLon) {

				newNode->pushFlashLat(lat);
				newNode->pushFlashLon(lon);
				newNode->pushFlashQuality(*(flashQualityData+j));
				newNode->pushFlashStrength(*(flashEnergyData+j)); //will push energy and also count 
			}
			//else dont do anything
			else {

			}
			
		}
		
		//check if the flash node is 0, if it is print that there were no flashes found and delete node
		if (newNode->getFlashCount() == 0) {
			std::cout << "No flashes found!" << std::endl;
			delete newNode; 
		}
		//else push that info to the textfile and write it out
		else {
			std::cout << "flashes found! " << std::endl;
			//file will be comma delimiated for easy excel use
			for(int j=0; j<newNode->getFlashLats().size(); j++){
				myfile << newNode->getFlashDate() << "," << newNode->getFlashLats()[j] << "," << newNode->getFlashLons()[j] << "," << newNode->getFlashStrength()[j] << "," << newNode->getFlashQuality()[j] << std::endl;
			}
			
			delete newNode;
	
		}
		
		delete[] flashLatData;
		delete[] flashLonData;
		delete[] flashEnergyData; 
		delete[] flashQualityData; 


	}
	
}

void netcdf::printAllInfoNodes() {
	for (int i = 0; i < pathInfo.size(); i++) {
		std::cout << "There were " << pathInfo[i].getFlashCount() << " flash events in file " << pathInfo[i].getFlashDate() << std::endl;
	}

}

std::vector<infoNode> netcdf::getInfoVector() { return pathInfo; }

std::string netcdf::getTextPath() { return textFilePath; }

///----------------------------------------------------------------
/// function definitions for infoNodes helper class
///---------------------------------------------------------------
infoNode::infoNode() {

}

void infoNode::pushFlashLat(const double &latitude) {
	flashlats.push_back(latitude); //used to store information on the latitude of a flash event
}

void infoNode::pushFlashLon(const double& longitude) {
	flashlons.push_back(longitude); //used to store information on the longitude of a flash event
}

void infoNode::pushFlashDate(const std::string &path) { //pass a full filepath object that is the full name of the file
	std::string substring = path.substr(path.length()-17, 14); //parses the string on my system to return just the relevant timestamp
	flashDate = substring; 
}

void infoNode::pushFlashStrength(const int &strength) {
	flashStrength.push_back(strength); //push the flashstrength and then count the event
	flashCount++; 
}

void infoNode::pushFlashQuality(const int& quality) {
	flashQuality.push_back(quality);
}

int infoNode::getFlashCount() {
	return flashCount; 
}

std::string infoNode::getFlashDate() {
	return flashDate; 
}

std::vector<double> infoNode::getFlashLons() {
	return flashlons;
}

std::vector<double> infoNode::getFlashLats() {
	return flashlats;
}

std::vector<int> infoNode::getFlashQuality() {
	return flashQuality;
}

std::vector<int> infoNode::getFlashStrength() {
	return flashStrength;
}