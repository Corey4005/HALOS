#include "classInterpolate.h"
#include "classDatetime.h"
#include "classCommand.h"
#include <iostream>
#include <string>
#include <vector>
#include <netcdf> //YAY WE GOT THE NETCDF FILES FROM VCPKG!!

int main() {

	Command obj; 
	obj.setLocation(30.30, -55.50, 30.86, -55.11);
	obj.calculateDistance(); 
	obj.calculateSpeedPerHour(3);
	obj.calculate20SecondDistance();
	obj.calculateNpoints();
	obj.interpolateLatLons();
	obj.printNpoints();
	obj.setDate(2021, 5, 20);
	obj.setTime(0, 0, 0);
	obj.set_dYear(); //day of year to get data from 
	obj.fillTimeVector(); 
	
}