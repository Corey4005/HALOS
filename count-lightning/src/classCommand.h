#ifndef CLASS_COMMAND_H
#define CLASS_COMMAND_H
#include "classDatetime.h"
#include "classInterpolate.h"
#include <string>
class Command : public Interpolate, public Datetime {
private:

	const std::string bucket = "noaa - goes16";
	const std::string product = "GLM-L2-LCFA"; 

public: 
	Command(); //default constructor
};
#endif
