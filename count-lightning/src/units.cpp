#include "units.h"
#include <iostream>


/* 
* module provides utility functions for performing angle conversions. 
* 
* Developer: Corey Walker 
* Github: Corey4005
* Version: 0.1
* 

*/

double radiansToDegrees(const double &radian) {
	/*
	* convert a radian angle to degrees.
	* 
	@param a radian value to convert to degrees. 
	@return returns degrees.  
	*/
	double degrees = (radian * 180.0) / M_PI;
	return degrees;
}

double arcminsToDegrees(const double& arcmin) {
	/* 
	* convert arcminute angle to degrees
	* 
	* @param an arcminute value to convert to degrees. 
	* @return returns degrees. 
	*/
	double degrees = arcmin / 60.0;
	return degrees; 
}

double arcsecsToDegrees(const double& arcsec) {
	/*
	* convert arcsec angle to degrees 
	* 
	* @param an arcsecond value to convert to degrees. 
	* @return returns degrees. 
	*/
	double degrees = arcsec / 3600.0; 
	return degrees; 
}

double degreesToRadians(const double& degree) {
	/*
	* convert degree angle to radians
	*
	* @param a degree value to convert to radians.
	* @return returns radians.
	*/
	double radians = degree * (M_PI / 180.0);
	return radians; 
}

double arcsecsToRadians(const double& arcsec) {
	/*
	* convert arcsec angle to radians
	*
	* @param an arcsec value to convert to radians.
	* @return returns radians.
	*/
	double radians = arcsec * (M_PI / (180.0 * 3600.0));
	return radians;
}

double arcminsToRadians(const double& arcmin) {
	/*
	* convert arcmin angle to radians
	* 
	* @param an arcminute value to convert to radians
	* @return returns radians
	*/
	double radians = arcmin * (M_PI / (60.0 * 180.0));
	return radians;
}

