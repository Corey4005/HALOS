#ifndef CLASS_COMMAND_H
#define CLASS_COMMAND_H
#include "classDatetime.h"
#include "classInterpolate.h"
#include <string>
#include <vector>

class Command : public Interpolate, public Datetime {
private:

	const std::string bucket = "noaa - goes16";
	const std::string product = "GLM-L2-LCFA"; 
	std::vector<int> hours; 

public: 
	Command(); //default constructor
	std::string createDownloadStrings(); 
	void fillTimeVector(); //fills timesArray with timestamps
	void getUniqueHours(); //function to set vector with unique hours from timestamps
	void printTimeVector(); //function to print all values from time vector
};
#endif
