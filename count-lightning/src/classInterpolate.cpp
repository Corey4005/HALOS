#include "classInterpolate.h"
#include "convertUnits.h"
#include <iostream>

	/* Implemetation file for class Interpolate.
	* 
	* This is a class to calculate the distance between two latitudes and longitudes
	* as the crow flies (haversine formula) and create the start and stop download strings
	* for AWS based on the input data. 
	*
	* 
	* Website explaining haversine: https://www.movable-type.co.uk/scripts/latlon.html
	* 
	*/

Interpolate::Interpolate() {

}


Interpolate::Interpolate(double lat1, double lon1, double lat2, double lon2) {
		latOne = lat1;
		lonOne = lon1;
		latTwo = lat2; 
		lonTwo = lon2;
}

void Interpolate::setLocation(double lat1, double lon1, double lat2, double lon2) {
		latOne = lat1;
		lonOne = lon1;
		latTwo = lat2;
		lonTwo = lon2;
}

void Interpolate::calculateDistance() {
		double phiOne = degreesToRadians(latOne); //latitude 1 in radians to be calculated
		double phiTwo = degreesToRadians(latTwo); //latitude 2 in radians to be calculated
		double deltaPhi = degreesToRadians((latTwo - latOne)); // change in Latitudes
		double deltaLambda = degreesToRadians((lonTwo - lonOne)); // change in Longitudes
		double a = sin(deltaPhi / 2) * sin(deltaPhi / 2) + cos(phiOne) * cos(phiTwo) * sin(deltaLambda / 2) * sin(deltaLambda / 2); 
		double c = atan2(sqrt(a), sqrt(1 - a));
		distance = (earthRadius * c)/1000.0; //distance in km
}

void Interpolate::calculateSpeedPerHour(double timeToPoint2) {
	speed = distance / timeToPoint2; 
}

void Interpolate::calculate20SecondDistance() {
	distance20 = (speed * 20.0) / 3600.0;
}

void Interpolate::calculateNpoints() {
	nPoints = distance / distance20;
}

void Interpolate::printDistance() {
		std::cout << "The distance between " << latOne << ", " << lonOne << " and " <<
			latTwo << ", " << lonTwo << " is " << distance << " kilometers" << std::endl;
}

void Interpolate::printSpeed() {
	std::cout << "The speed of the storm event is " << speed << 
		" kilometers per hour." << std::endl; 
}

void Interpolate::print20SecondDistance() {
	std::cout << "The 20 second distance of the storm event is " << distance20 <<
		" kilometers." << std::endl;
}

void Interpolate::printNpoints() {
	std::cout << "The number of 20 second time intervals are " << 
		nPoints << std::endl;
}

int Interpolate::getNpoints() {
	return nPoints; 
}

void Interpolate::interpolateLatLons() {
	double latDis = abs(((latTwo - latOne) / nPoints));
	double lonDis = abs((lonTwo - lonOne) / nPoints); 
	double tempLatOne = latOne; 
	double tempLonOne = lonOne;
	for (int i = 0; i < (nPoints-1); i++) {
		tempLatOne += latDis;
		tempLonOne += lonDis;
		newLats.push_back(tempLatOne);
		newLons.push_back(tempLonOne);
	}
	
}

std::vector<double> Interpolate::getInterpolatedLats(){ return newLats; }

std::vector<double> Interpolate::getInterpolatedLons() { return newLons; }