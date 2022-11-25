
#include <iostream>
#include "units.h"

int main() {
	const double radians = M_PI/3; // pi over 3 radians
	const double arcmins = 3.0; //three arcminutes 
	const double arcsecs = 5000.0; //five thousand arcseconds
	const double degrees = 90.0; //right angle in degrees

	//example of radians to degrees
	std::cout << "radians: " << radians << ", " << "degrees: " << radiansToDegrees(radians) << std::endl;
	std::cout << "\n";

	//example of arcmins to degrees 
	std::cout << "arcminutes: " << arcmins << ", " << "degrees: " << arcminsToDegrees(arcmins) << std::endl;
	std::cout << "\n";

	//example of arcmins to degrees
	std::cout << "arcseconds: " << arcsecs << ", " << "degrees: " << arcsecsToDegrees(arcsecs) << std::endl;
	std::cout << "\n";

	//example of degrees to radians 
	std::cout << "degrees: " << degrees << ", " << "radians: " << degreesToRadians(degrees) << std::endl;
	std::cout << "\n";

	//example of arcsecs to radians
	std::cout << "arcseconds: " << arcsecs << ", " << "radians: " << arcsecsToRadians(arcsecs) << std::endl;
	std::cout << "\n";

	//example of arcmins to radians
	std::cout << "arcminutes: " << arcmins << ", " << "radians: " << arcminsToRadians(arcmins) << std::endl;
	std::cout << "\n";


	std::cin.get();  
}