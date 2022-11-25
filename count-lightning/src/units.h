#pragma once
#define _USE_MATH_DEFINES
#include <cmath>

//function declarations for linker 
// 
	//to convert various types to degrees
double radiansToDegrees(const double& radian); 
double arcminsToDegrees(const double& arcmin);
double arcsecsToDegrees(const double& arcsec);

	//to convert various types to radians
double degreesToRadians(const double& degree);
double arcminsToRadians(const double& arcmin);
double arcsecsToRadians(const double& arcsec);