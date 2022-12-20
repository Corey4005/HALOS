#ifndef CLASS_COMMAND_H
#define CLASS_COMMAND_H
#include "classDatetime.h"
#include "classInterpolate.h"
#include <string>
#include <vector>

class Command : public Interpolate, public Datetime {
private:

	
	std::vector<int> hours; 

public: 
	Command(); //default constructor
	void fillTimeVector(); //fills timesArray with timestamps
	void getUniqueHours(); //function to set vector with unique hours from timestamps
	void printTimeVector(); //function to print all values from time vector
	const std::string bucket = "noaa-goes16";
	const std::string product = "GLM-L2-LCFA";
	const std::string filestart = "OR_GLM-L2-LCFA_G16_"; //represents file start path
};
#endif
