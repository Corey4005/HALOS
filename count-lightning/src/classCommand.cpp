#include "classCommand.h"
#include <string>
#include <vector>
#include <iostream>
#include <filesystem>
#include "awsS3.h"


Command::Command() {
	//default constructor
}

std::string Command::getcwd() {
	return cwd;
}


