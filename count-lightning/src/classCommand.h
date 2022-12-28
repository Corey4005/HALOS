#ifndef CLASS_COMMAND_H
#define CLASS_COMMAND_H
#include "classDatetime.h"
#include "classInterpolate.h"
#include "classNetCDF.h"
#include <string>
#include <vector>
#include <filesystem>
#include "awsS3.h"



class Command : public netcdf {
private:
	std::string cwd = std::filesystem::current_path().string();

public: ;
	Command(); //default constructor
	std::string getcwd();
};
#endif
