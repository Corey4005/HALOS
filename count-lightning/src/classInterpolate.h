#ifndef INTERPOLATE_H
#define INTERPOLATE_H
#include <vector>

/* declaration file for class Distance class
* 
*/
class Interpolate {
	friend class netcdf;
	const double earthRadius = 6371e3; //earth's mean earth radius
	double distance = 0.0; //the distance in kilometers between two latitudes and longitudes
	double speed = 0.0;
	double distance20 = 0.0;
	double latOne = 0.0;
	double lonOne = 0.0;
	double latTwo = 0.0;
	double lonTwo = 0.0;
	std::vector<double> newLats;
	std::vector<double> newLons;
protected:
	double nPoints = 0.0;
public: 
	Interpolate();
	Interpolate(double latOne, double longOne, double latTwo, double lonTwo);
	void setLocation(double latOne, double longOne, double latTwo, double lonTwo);
	void calculateDistance();
	void printDistance();
	void calculateSpeedPerHour(double timeToPoint2);
	void printSpeed();
	void calculate20SecondDistance();
	void print20SecondDistance();
	void calculateNpoints();
	int getNpoints(); 
	void printNpoints();
	void interpolateLatLons();
	std::vector<double> getInterpolatedLats();
	std::vector<double> getInterpolatedLons();
};

#endif