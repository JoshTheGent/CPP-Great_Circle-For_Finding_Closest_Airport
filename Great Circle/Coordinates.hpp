#include <string>
#include <iostream>
#include <math.h>

// CLASS FOR USER INPUT //
class InputCoordinates
{
public:
	//constructor//
	InputCoordinates()
	{
	}

	InputCoordinates(std::string name, double latitude, double longitude, double altitude)
	{
		Name = name;
		Latitude = latitude;
		Longitude = longitude;
		Altitude = altitude;
	}
	//atributes//
	std::string Name;
	double Latitude;
	double Longitude;
	double Altitude;
};

// CLASS FOR FILE INPUT //
class FileCoordinates
{
public:
	//constructor//
	FileCoordinates()
	{
	}

	FileCoordinates(std::string name, double latitude, double longitude, double altitude)
	{
		Name = name;
		Latitude = latitude;
		Longitude = longitude;
		Altitude = altitude;
	}

	//atributes//
	std::string Name;
	double Latitude;
	double Longitude;
	double Altitude;
};